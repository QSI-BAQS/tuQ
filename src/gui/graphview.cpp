//
// statement of purpose
//
# include "graphview.hpp"

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
      setCursorLabel(event->text());
      cursorState= true;
/*  Q2Graph code includes this + comment for Qt::Key_Z
      clearSelection()
*/
      QGraphicsView::keyPressEvent(event);
   }
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
      QLineF growline(tracer->line().p1(), event->screenPos());
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
      QPoint vpos= event->pos();
      QGraphicsItem * edge_origin= itemAt(vpos);

      // prevent runtime exception of no vertex at the cursor hotspot at
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
      tracer= new QGraphicsLineItem(QLineF(vpos,vpos));
      tracer->setPen(QPen(Qt::black,2));

      scene->addItem(tracer);

      // reset cursor state
      cursorState= false;
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
      auto * v= new GraphVertex(nullptr, vertices_count);   // TO DO: initialise, contextmenu
      vertices_count += 1;

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

}


// private:
void GraphView::setCursorLabel(QString tag) {
   // create E/O/V/X/Y/Z label for cursor
   // pre-condition: cursorState == true
   // post-condition: a visible, persistent label of the cursor

   if (cursorState){
      // label appears at (x,y), relative to cursor
      clabel->move(QCursor::pos().x() + 15, QCursor::pos().y() + 10);

      // set label
      tag.isLower() ? clabel->setText(tag.toUpper()) : clabel->setText(tag);

      // reveal a hidden cursor
      if (clabel->isHidden())
         clabel->show();
   }
}