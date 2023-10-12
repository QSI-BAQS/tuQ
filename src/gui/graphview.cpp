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
   // *** TO DO: all rows, 67 columns accessible ***
   scene->setSceneRect(-5000,-5000,10000,10000);

   setScene(scene);
   setMouseTracking(true);

   clabel= new QLabel;
   clabel->setWindowFlag(Qt::ToolTip);
//   clabel->setWindowOpacity(0);
}


// read instructions, format .txt
void GraphView::openGraph(const QString & rfile) {
   QFile loadfile(rfile);

   // read conditions: read-only, text
   if (!loadfile.open(QIODevice::ReadOnly | QIODevice::Text)){
      qDebug() << " file is not open";
      return ;
   }

   QTextStream in_stream(&loadfile);
   QString vertex_data {in_stream.readLine()};

   while (!vertex_data.isNull()) {
      QStringList stats= vertex_data.split(QChar(' '));
      // 1. reproduce vertex
      unsigned long vid= stats.at(0).toULong();
      auto * v= new GraphVertex(nullptr, vid);   // TO DO: initialise, contextmenu

      // set vertex position
      double x= stats.at(1).toDouble();
      double y= stats.at(2).toDouble();
      v->setPos(x,y);

      // add vertex to scene
      scene->addItem(v);

      // 2a. accumulate 'opposite edges'
      if (stats.size() > 3){
         double epos_x;
         double epos_y;
         unsigned long edge_coordinates {1};

         for (int counter= 3; counter < stats.size() ; ++counter) {
            if (edge_coordinates % 2 == 0){
               epos_y= stats.at(counter).toDouble();
               QPointF end_pos {epos_x,epos_y};
               v->opposite_ends.push_back(end_pos);
               epos_x= 0;
               epos_y= 0;
            }
            else
               epos_x= stats.at(counter).toDouble();

            edge_coordinates += 1;
         }
      }
      vertex_data= in_stream.readLine();
   }

   loadfile.close();

   // 2b. reproduce edges
   for (QGraphicsItem * item : scene->items()) {
      // only type GraphVertex
      if (item->type() == 4){
         auto v{qgraphicsitem_cast<GraphVertex *>(item)};
         // does v carry edges?
         if (!v->opposite_ends.isEmpty()){
            for (QPointF vpos : qAsConst(v->opposite_ends)) {
               // a QPointF element of opposite_ends does not align with any
               // QPointF of scene coordinates; swap vpos for item->pos()...
               QPoint item_xy {(int) vpos.x(), (int) vpos.y()};
               // then locate item @ item coordinates within scene
               QGraphicsItem * ptr_other_v= scene->itemAt(mapToParent(item_xy)
                     , QTransform());
               auto other_v= qgraphicsitem_cast<GraphVertex *>(ptr_other_v);
               // confirm the opposite end is type GraphVertex
               if (other_v->type() == 4){
                  GraphEdge * e= new GraphEdge(v,other_v, nullptr);
                  v->addEdge(e);
                  other_v->addEdge(e);

                  scene->addItem(e);
               }
            }
            v->opposite_ends.clear();
         }
      }
   }
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

      set_lattice(cluster_state_rows, cluster_state_columns);
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
         // edge coordinates (unique: no 'flips')
         for (const GraphEdge * e: *v->alledges) {
            if (e->p1vertex
            && e->p1vertex->x() != v->pos().x()
            && e->p1vertex->y() != v->pos().y())
               write << " " << e->p1vertex->x() << " " << e->p1vertex->y();
            if (e->p2vertex
            && e->p2vertex->x() != v->pos().x()
            && e->p2vertex->y() != v->pos().y())
               write << " " << e->p2vertex->x() << " " << e->p2vertex->y();
         }
         write << "\n";
      }
   }
   writefile.flush();
   writefile.close();
}

void GraphView::set_lattice(unsigned long m, unsigned long n) {
//   circuit-to-graph layout
//   pre-condition:
//      - json input is well-formed,
//      - composition and layout of gates passes input checks.
//   post-condition: the count of measurement patterns, including edges,
//      strictly reconciles with the count of (input) circuit gates
   unsigned long id {1};
   qreal xinc {75};
   qreal yinc {75};

   for (int i= 0; i < m; ++i) {
      for (int j= 0; j < n; ++j) {
         auto vertex= new GraphVertex(nullptr,id);   // TO DO: initialise, contextmenu
         vertex->setPos(j*xinc,i*yinc);
         scene->addItem(vertex);

         id += 1;
      }
   }
   // *** TO DO: set edges (rejig h_localComplementation logic?) ***
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
   // TO DO, LPM X abort insert

   // instantiate: GraphEdge, pt. 1
   if (clabel->text() == "E"){
      // collect the p1 vertex at the cursor hotspot at 'click'
      QPoint vertex_at_view= event->pos();
      QPointF vertex_at_scene= mapToScene(vertex_at_view);
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
      // reset cursor state
      cursorState= false;
      clabel->clear();
   }
   // instantiate: GraphVertex
   else if (clabel->text() == "V"){
      // instantiate the vertex
      unsigned long v_count= h_item_counter(4, scene);
      auto * v= new GraphVertex(nullptr, v_count);   // TO DO: initialise, contextmenu

      // place vertex at 'click' position
      QPointF pos_xy= mapToScene(event->x()-15, event->y());
      v->setPos(pos_xy);

      scene->addItem(v);

      // reset cursor state
      cursorState= false;
      clabel->clear();
   }
   // measurement, x-basis
   else if (clabel->text() == "X"){
      // reset cursor state
      cursorState= false;
      clabel->clear();
   }
   // measurement, y-basis
   else if (clabel->text() == "Y"){
      // reset cursor state
      cursorState= false;
      clabel->clear();
   }
   // measurement, z-basis
   else if (clabel->text() == "Z"){
      // reset cursor state
      cursorState= false;
      clabel->clear();
   }

   QGraphicsView::mousePressEvent(event);
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
         GraphVertex * p1v= qgraphicsitem_cast<GraphVertex *>(p1items.first());
         // restore the 'movable' property of p1v, which was suspended at
         // mousePressEvent
         p1v->setFlag(QGraphicsItem::ItemIsMovable, true);
         // drop focus from p1v
         p1v->setSelected(false);
         // pointer -> the GraphVertex at p2 coordinates
         GraphVertex * p2v= qgraphicsitem_cast<GraphVertex *>(p2items.first());
         // use p1v and p2v as constructors to instantiate the edge
         auto * e= new GraphEdge(p1v, p2v, nullptr);   // TO DO: initialise, contextmenu

         // add the edge to (QVector) 'edges' of vertices at both p1 and p2
         // coordinates
         p1v->addEdge(e);
         p2v->addEdge(e);

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