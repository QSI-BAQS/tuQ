//
// specify view/scene objects
//
# include "graphview.hpp"

#include <QFile>
#include <QKeyEvent>


// public:
GraphView::GraphView(QWidget *parent)
   : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
   scene->setSceneRect(-1500,-1500,3000,3000);

   setScene(scene);
   setMouseTracking(true);

   clabel= new QLabel;
   clabel->setWindowFlag(Qt::ToolTip);
   clabel->setWindowOpacity(0);
}

// count of items in scene by QGraphicsItem::Type
unsigned long GraphView::items_count(int item_type) {
   unsigned long counter {1};
   for (QGraphicsItem * item : scene->items()) {
      (item->type() == item_type) ? counter += 1 : counter= 0;
   }

   return counter;
}

// read instructions for file (.txt) loading
void GraphView::openGraph(QString rfile) {}

// write instructions for file (.txt) saving
void GraphView::saveGraph(QString wfile) const {}

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
}


// protected:
void GraphView::keyPressEvent(QKeyEvent * event) {
   if (event->key() == Qt::Key_E
   || event->key() == Qt::Key_O
   || event->key() == Qt::Key_V
   || event->key() == Qt::Key_X
   || event->key() == Qt::Key_Y
   || event->key() == Qt::Key_Z){
      cursorState= true;

      cursor_tag= event->text();
      setCursorLabel(& cursor_tag);
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
      QGraphicsItem * edge_origin= scene->itemAt(vertex_at_scene,transform());

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
      unsigned long v_count= items_count(4);
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
void GraphView::setCursorLabel(QString * tag) {
   // create E/O/V/X/Y/Z label for cursor
   // pre-condition: cursorState == true
   // post-condition: a visible, persistent label of the cursor

   if (cursorState){
      // label appears at (x,y), relative to cursor
      QPoint cursor_pos {QCursor::pos().x() + 15, QCursor::pos().y() + 10};
      clabel->move(cursor_pos);

      // set label
      tag->isLower() ? clabel->setText(tag->toUpper()) : clabel->setText(* tag);

      // reveal a hidden cursor
      if (clabel->isHidden())
         clabel->show();
   }
}