//
// specify view/scene objects
//
# include "graphview.hpp"

#include <QDebug>
#include <QFile>
#include <QKeyEvent>
#include <QTextStream>


// public:
GraphView::GraphView(QWidget *parent)
   : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
   // '... one unit on the scene is represented by one pixel on the screen.'
   // *** ~[121, 121] accessible at this sceneRect ***
   /* FIX: setSceneRect has to be consistent between this and setLattice otherwise
      lattice created in one set of coordinates do not show up in the other set */
   scene->setSceneRect(-2500,-2500,11000,11000);

   setScene(scene);
   setMouseTracking(true);

   clabel= new QLabel;
   clabel->setWindowFlag(Qt::ToolTip);
//   clabel->setWindowOpacity(0);

   createElementMenus(scene);
}


// read instructions, format .txt
void GraphView::openGraph(const QString & rfile) {
   QFile loadfile(rfile);

   // read conditions: read-only, text
   if (!loadfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << " file is not open";
      return;
   }

   QTextStream in_stream(&loadfile);

   // 1. place all vertices
   QString vertex_data{in_stream.readLine()};

   while (!vertex_data.isNull()) {
      QStringList vertex_stats = vertex_data.split(QChar(' '));
      // reproduce vertex
      unsigned long vid = vertex_stats.at(0).toULong();
      auto *v = new GraphVertex(vertexmenu, vid);

      // set vertex position
      double x = vertex_stats.at(1).toDouble();
      double y = vertex_stats.at(2).toDouble();
      v->setPos(x, y);

      // add vertex to scene
      scene->addItem(v);

      vertex_data = in_stream.readLine();
   }
   // return pointer to beginning of in_stream
   in_stream.seek(0);

   // 2. place all edges
   QString edges_data{in_stream.readLine()};

   while (!edges_data.isNull()) {
      QStringList edge_stats = edges_data.split(QChar(' '));
      // reproduce edge
      if (edge_stats.size() > 3) {
         // details of 'reference' vertex
         double x= edge_stats.at(1).toDouble();
         double y= edge_stats.at(2).toDouble();
         QPointF v_pos {x, y};
         QGraphicsItem * ptr_ref_item= scene->itemAt(
               mapToParent(v_pos.toPoint()),QTransform());
         auto ref_v= qgraphicsitem_cast<GraphVertex *>(ptr_ref_item);

         // edge_i coordinates
         double epos_x;
         double epos_y;
         unsigned long edge_coordinates{1};

         for (int counter= 3; counter < edge_stats.size() ; ++counter) {
            if (edge_coordinates % 2 == 0){
               epos_y= edge_stats.at(counter).toDouble();
               QPointF end_pos {epos_x,epos_y};

               // map end_pos to (scene) then, locate (vertex) within scene
               QGraphicsItem * ptr_other_v= scene->itemAt(
                     mapToParent(end_pos.toPoint()), QTransform());
               auto other_v= qgraphicsitem_cast<GraphVertex *>(ptr_other_v);
               // other_v is type GraphVertex?
               if (other_v->type() == 4){
                  auto * e= new GraphEdge(ref_v, other_v, edgemenu);
                  ref_v->add_edge(e);
                  other_v->add_edge(e);

                  scene->addItem(e);
               }

               epos_x= 0;
               epos_y= 0;
            }
            else
               epos_x= edge_stats.at(counter).toDouble();

            edge_coordinates += 1;
         }
      }

      edges_data = in_stream.readLine();
   }

   loadfile.close();
}

// read a quantum circuit file, format .json (schemas: 'native', which is
// adapted from ionQ; and Google Cirq, which is reformatted to the native
// schema). See comments of src/layout/io_circuit.cpp.
void GraphView::readCircuit(const QString & cjson) {
   // convert QString to utf8 string
   std::string cjson_utf8= cjson.toUtf8().constData();
   std::ifstream json_circuit {cjson_utf8};

   if (json_circuit.is_open()){
      using json= nlohmann::json;

      json parse_circuit= json::parse(json_circuit);   // create json object
      auto cirq_check= parse_circuit.find("cirq_type");

      if (cirq_check != parse_circuit.end()){
         // format of input circuit json: cirq
         json ionq_schema= cirq_to_ionq_schema(parse_circuit);
         etch_circuit= ionq_schema;
      }
      // format of input circuit json: ionQ
      else {
         if (non_adjacent_gate(parse_circuit))
            qDebug() << "process aborted: non-adjacent gate in circuit";

         etch_circuit= parse_circuit;
      }

      unsigned long cluster_state_rows= rows_m(gate_by_address, etch_circuit);
      unsigned long cluster_state_columns= cols_n(gate_by_address
            , etch_circuit);

      setLattice(cluster_state_rows, cluster_state_columns);
   }
   else
      qDebug() << "That file is not opening";
}

// write instructions, format .txt
void GraphView::saveGraph(const QString & wfile) {
   QFile writefile(wfile);

   // save conditions: write-only, text
   if (!writefile.open(QIODevice::WriteOnly | QIODevice::Text)){
      qDebug() << " file is not open";
      return ;
   }

   QTextStream write(&writefile);
   for (QGraphicsItem * item : scene->items()) {
      // save only type GraphVertex specifications
      if (item->type() == 4){
         auto v= qgraphicsitem_cast<GraphVertex *>(item);
         // vertex ID
         write << *v->vertexID << " "
         // vertex pos
         << v->pos().x() << " " << v->pos().y();
         // edge coordinates (unique, i.e. no 'flips')
         for (const GraphEdge * e: *v->alledges) {
            if ((e->p1vertex->x() != v->pos().x() &&
            e->p2vertex->x() == v->pos().x())
            && (e->p1vertex->y() != v->pos().y() &&
            e->p2vertex->y() == v->pos().y()))
               write << " " << e->p2vertex->x() << " " << e->p2vertex->y();
            else
               write << " " << e->p1vertex->x() << " " << e->p1vertex->y();
         }
         write << "\n";
      }
   }
   writefile.flush();
   writefile.close();
}

void GraphView::setLattice(unsigned long m, unsigned long n) {
//   define graph layout, by circuit input or menu option
//   pre-condition (from circuit input):
//      - json input is well-formed,
//      - composition and layout of gates passes input checks.
//   post-condition (from circuit input): the count of measurement patterns,
//       including edges, reconciles with the count of (input) circuit gates
   unsigned long id {1};
   qreal xinc {70};
   qreal yinc {70};
/*
 * 31-JAN-24 the coordinates from a setLattice graph don't match the default
 *    setSceneRect

   // resize for big [m,n]
   // ~ 3 seconds to render [501,501]; ~ 12 seconds to render [1001,1001]
   scene->setSceneRect(-50, -50, qreal (n*101), qreal (m*101));
   setAlignment(Qt::AlignTop | Qt:: AlignLeft);
   show();
*/
   GraphVertex * row_to_row_edges[n];
   GraphVertex * ptr_vertex {};

   for (int i= 0; i < m; ++i) {
      for (int j= 0; j < n; ++j) {
         // create vertex[row, column]
         auto vertex= new GraphVertex(vertexmenu,id);
         vertex->setPos(j*xinc,i*yinc);
         scene->addItem(vertex);

         // by row, edge-per-column
         if (j > 0){
            auto * column_edge= new GraphEdge(ptr_vertex, vertex, edgemenu);
            ptr_vertex->add_edge(column_edge);
            vertex->add_edge(column_edge);
            scene->addItem(column_edge);
         }
         // by column, edge-per-row
         if (i > 0){
            auto * row_edge= new GraphEdge(row_to_row_edges[j], vertex, edgemenu);
            row_to_row_edges[j]->add_edge(row_edge);
            vertex->add_edge(row_edge);
            scene->addItem(row_edge);
         }

         // assemble (Graph-)vertices of previous row
         ptr_vertex= vertex;
         row_to_row_edges[j]= ptr_vertex;

         id += 1;
      }
   }
}


// protected:
void GraphView::keyPressEvent(QKeyEvent * event) {
   // Esc to cancel out of function
   if (cursorState && event->key() == Qt::Key_Escape){
      clabel->clear();
      cursorState= false;
   }

   if (event->key() == Qt::Key_E
   || event->key() == Qt::Key_O
   || event->key() == Qt::Key_V
   || event->key() == Qt::Key_X
   || event->key() == Qt::Key_Y
   || event->key() == Qt::Key_Z){
      cursorState= true;
      setCursorLabel(event->key());
/*  Q2Graph code includes this + comment for Qt::Key_Z
      clearSelection()
*/
   }
   QGraphicsView::keyPressEvent(event);
}

void GraphView::mouseMoveEvent(QMouseEvent * event) {
   // position the label at x,y relative to cursor
   if (cursorState){
      auto qmex {(int) event->screenPos().x()};
      auto qmey{(int) event->screenPos().y()};

      clabel->move(qmex + 15, qmey + 10);
   }

   // draw the proxy (Graph)Edge instantiated through mousePressEvent
   if (tracer != nullptr && clabel->text() == "E"){
      QLineF growline(tracer->line().p1(), mapToScene(event->pos()));
      tracer->setLine(growline);
   }
   QGraphicsView::mouseMoveEvent(event);
}

void GraphView::mousePressEvent(QMouseEvent * event) {
   // LEFT click events
   if (event->button() != Qt::LeftButton)
      return ;

   // ABORT X measurement: user has not completed the X measurement in
   // contiguous steps (see 'part 2 -> measurement, x-basis', below)
   if (clabel->text() != "X" && !vertex1_X_neighbours.isEmpty()){
      for (GraphVertex * v : vertex1_X_neighbours) {
         v->resetVertexColour(Qt::black);
      }
      vertex1_X_neighbours.clear();
      vertex1_X= nullptr;
   }

   // instantiate: GraphEdge, pt. 1
   if (clabel->text() == "E"){
      // collect the p1 vertex at the cursor hotspot at 'click'
      QPointF vertex_at_scene= mapToScene(event->pos());
      QGraphicsItem * edge_origin= scene->itemAt(vertex_at_scene,QTransform());

      // prevent runtime exception from no vertex at the cursor hotspot upon
      // 'click'
      if (edge_origin == nullptr){
         cursorState= false;
         clabel->clear();
         return ;
      }
      else
         edge_origin->setFlag(QGraphicsItem::ItemIsMovable, false);

      // initialise a 'tracer' line segment.  The actual edge will be set in
      // arrears at the subsequent mouseReleaseEvent
      tracer= new QGraphicsLineItem(QLineF(vertex_at_scene, vertex_at_scene));
      tracer->setPen(QPen(Qt::black,2));
      scene->addItem(tracer);

      // reset cursor state
      cursorState= false;
      // 'E' is required as a boolean proxy in subsequent QMouseEvents
      clabel->hide();
   }
   // local complementation
   else if (clabel->text() == "O"){
      // specify in-focus vertex
      QPointF lcv_pos= mapToScene(event->pos());
      QGraphicsItem * item= scene->itemAt(lcv_pos,QTransform());
      auto lcv= qgraphicsitem_cast<GraphVertex *>(item);

      // helper function
      h_localComplementation(*lcv, *scene, edgemenu);

      // reset cursor state
      cursorState= false;
      clabel->clear();
   }
   // instantiate: GraphVertex
   else if (clabel->text() == "V"){
      // instantiate the vertex
      unsigned long v_count= h_itemCounter(4, *scene);
      auto * v= new GraphVertex(vertexmenu, v_count);

      // place vertex at 'click' position
      QPointF pos_xy= mapToScene(event->x()-15, event->y());
      v->setPos(pos_xy);

      scene->addItem(v);

      // reset cursor state
      cursorState= false;
      clabel->clear();
   }
   // part 1 -> measurement, x-basis
   else if (clabel->text() == "X" && vertex1_X_neighbours.isEmpty()){
      // select first vertex of X measurement
      QPointF x_vertex1_pos= mapToScene(event->pos());
      QGraphicsItem * item= scene->itemAt(x_vertex1_pos, QTransform());
      // 'item' is type GraphVertex or abort
      if (item == nullptr || item->type() != GraphVertex::Type){
         cursorState= false;
         clabel->clear();
         return ;
      }
      vertex1_X = qgraphicsitem_cast<GraphVertex *>(item);

      // ABORT: first vertex must have >= 1 edge for local complementation
      if (vertex1_X->alledges->isEmpty()){
         cursorState= false;
         clabel->clear();
         return ;
      }

      // populate neighbours of first vertex
      for (GraphEdge *e : *vertex1_X->alledges) {
         // obtain the address of underlying GraphVertex
         GraphVertex *address_of_p1vertex= e->p1vertex;
         // test whether pointed-at-objects are equivalent by comparing their
         // addresses
         if (address_of_p1vertex != vertex1_X)
            vertex1_X_neighbours.push_back(e->p1vertex);
         else
            vertex1_X_neighbours.push_back(e->p2vertex);
      }

      // reformat each of first vertex's neighbours as a prompt to the user to
      // select the special neighbour vertex
      for (GraphVertex *neighbour : vertex1_X_neighbours) {
         neighbour->resetVertexColour(QColor(0, 255, 0), 4, QColor(173, 255, 47));
      }
   }
   // part 2 -> measurement, x-basis
   else if (clabel->text() == "X" && !vertex1_X_neighbours.isEmpty()){
      // select special neighbour vertex of X measurement
      QPointF x_vertex2_pos= mapToScene(event->pos());
      QGraphicsItem * item= scene->itemAt(x_vertex2_pos, QTransform());
      // 'item' is type GraphVertex or abort
      if (item == nullptr || item->type() != GraphVertex::Type){
         for (GraphVertex * v : vertex1_X_neighbours) {
            v->resetVertexColour(Qt::black);
         }
         vertex1_X_neighbours.clear();
         vertex1_X= nullptr;

         cursorState= false;
         clabel->clear();
         return ;
      }
      auto vertex2_X= qgraphicsitem_cast<GraphVertex *>(item);

      // ABORT: special neighbour vertex must have >= 1 edge for local
      // complementation
      if (vertex2_X->alledges->isEmpty()){
         cursorState= false;
         clabel->clear();
         return ;
      }

      // first local complementation on special neighbour vertex
      h_localComplementation(*vertex2_X, *scene, edgemenu);

      // restore each of first vertex's neighbours to default colour scheme
      for (GraphVertex * v : vertex1_X_neighbours) {
         v->resetVertexColour(Qt::black);
      }

      // Y measurement of first vertex
      h_localComplementation(*vertex1_X, *scene, edgemenu);
      h_deleteVertex(*vertex1_X, *scene);

      // second local complementation on special neighbour vertex
      h_localComplementation(*vertex2_X, *scene, edgemenu);

      // clean up
      vertex1_X_neighbours.clear();
      vertex1_X= nullptr;

      // reset cursor state
      cursorState= false;
      clabel->clear();
   }
   // measurement, y-basis
   else if (clabel->text() == "Y"){
      // select vertex of Y measurement
      QPointF vertex_at_scene= mapToScene(event->pos());
      QGraphicsItem * y_item= scene->itemAt(vertex_at_scene, QTransform());
      auto * y_vertex= qgraphicsitem_cast<GraphVertex *>(y_item);

      // prevent the exception caused by no object at cursor hotspot upon
      // 'click'
      if (y_vertex != nullptr){
         if (y_vertex->alledges->isEmpty())
            h_deleteVertex(*y_vertex, *scene);
         else if (!y_vertex->alledges->isEmpty()){
            h_localComplementation(*y_vertex, *scene, edgemenu);
            h_deleteVertex(*y_vertex, *scene);
         }
      }

      // reset cursor state
      cursorState= false;
      clabel->clear();
   }
   // measurement, z-basis
   else if (clabel->text() == "Z"){
      // select vertex of Z measurement
      QPointF vertex_at_scene= mapToScene(event->pos());
      QGraphicsItem * z_item= scene->itemAt(vertex_at_scene, QTransform());
      auto * z_vertex= qgraphicsitem_cast<GraphVertex *>(z_item);

      if (z_vertex != nullptr)
         h_deleteVertex(*z_vertex,*scene);

      // reset cursor state
      cursorState= false;
      clabel->clear();
   }

   QGraphicsView::mousePressEvent(event);
   scene->update();
}

void GraphView::mouseReleaseEvent(QMouseEvent * event) {
   // instantiate: GraphEdge, pt. 2
   if (tracer != nullptr && clabel->text() == "E"){
      // staging: the vertex identified at p1 coordinates
      QList<QGraphicsItem *> p1items= scene->items(tracer->line().p1());
      // remove any existing instance of tracer in p1items
      if (p1items.count() && p1items.first() == tracer)
         p1items.removeFirst();

      // staging: the vertex identified at p2 coordinates
      QList<QGraphicsItem *> p2items= scene->items(tracer->line().p2());
      // as with p1items, remove any existing instance of tracer
      if (p2items.count() && p2items.first() == tracer)
         p2items.removeFirst();

      // vertices at p1 and p2 now selected so back out the tracer reference
      // from scene...
      scene->removeItem(tracer);
      // then, deallocate the memory
      delete tracer;

      if (p1items.count() > 0 && p2items.count() > 0
      && p1items.first()->type() == GraphVertex::Type
      && p2items.first()->type() == GraphVertex::Type
      && p1items.first() != p2items.first()){
         // pointer -> the GraphVertex at p1 coordinates
         auto * p1v= qgraphicsitem_cast<GraphVertex *>(p1items.first());
         // restore the 'movable' property of p1v, which was suspended at
         // mousePressEvent
         p1v->setFlag(QGraphicsItem::ItemIsMovable, true);
         // drop focus from p1v
         p1v->setSelected(false);
         // pointer -> the GraphVertex at p2 coordinates
         auto * p2v= qgraphicsitem_cast<GraphVertex *>(p2items.first());
         // use p1v and p2v as constructors to instantiate the edge
         auto * e= new GraphEdge(p1v, p2v, edgemenu);

         // add the edge to (QVector) 'edges' of vertices at both p1 and p2
         // coordinates
         p1v->add_edge(e);
         p2v->add_edge(e);

         scene->addItem(e);

         // clear the (mousePressEvent) clabel->hide()
         if (clabel->text() == "E")
            clabel->clear();
      }
   }
   tracer= nullptr;
   QGraphicsView::mouseReleaseEvent(event);
}


// private:
void GraphView::createElementMenus(QGraphicsScene * graph_scene) {
   // right-click menus for graph elements, (Graph)edge and (Graph)vertex
   edgemenu= new QMenu("edge menu");
   edgemenu->addAction(tr("&Delete"), this, [&, graph_scene](){
      // collect only the edge at the cursor hotspot, upon 'click'
      QList<QGraphicsItem *> del_edge= graph_scene->selectedItems();
      // either head of del_edge is type GraphEdge or abort
      if (del_edge.isEmpty() || del_edge.first()->type() != GraphEdge::Type)
         return ;

      // delete edge
      auto * edge= qgraphicsitem_cast<GraphEdge *>(del_edge.first());
      h_deleteEdge(edge, *graph_scene);
   });
//   edgemenu->addAction(tr("-- place 2 --"));

   vertexmenu= new QMenu("vertex menu");
   vertexmenu->addAction(tr("&Delete"), this, [&, graph_scene](){
      // collect only the vertex at the cursor hotspot, upon 'click'
      QList<QGraphicsItem *> del_vertex= graph_scene->selectedItems();
      // either head of del_vertex is type GraphVertex or abort
      if (del_vertex.isEmpty() || del_vertex.first()->type() != GraphVertex::Type)
         return ;

      // delete vertex
      auto * vertex= qgraphicsitem_cast<GraphVertex *>(del_vertex.first());
      h_deleteVertex(*vertex, *graph_scene);
   });
//   vertexmenu->addAction(tr("-- place 2 --"));
}

void GraphView::setCursorLabel(int key) {
   // create E/O/V/X/Y/Z label for cursor
   // pre-condition: cursorState == true
   // post-condition: a visible, persistent label of the cursor

   // int to upper case QString
   QString tag= (QString) toupper(key);

   if (cursorState){
      // label appears at (x,y), relative to cursor
      QPoint cursor_pos {QCursor::pos().x() + 15, QCursor::pos().y() + 10};
      clabel->move(cursor_pos);

      // set label
      clabel->setText(tag);

      // reveal a hidden cursor
      if (clabel->isHidden())
         clabel->show();
   }
}
