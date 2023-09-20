//
// specify a vertex object
//
#include "graphedge.hpp"
#include "graphvertex.hpp"


// public:
GraphVertex::GraphVertex(QMenu * menu, unsigned long vid
                         , QGraphicsItem * parent)
   : QGraphicsEllipseItem(parent), contextmenu_v(menu), vertexid(vid) {
   // standard vertex: fill, circumference pen
   setRect(vertexboundaryrect);
   setBrush(vertexfill);
   setPen(vertexcircumferencepen);

   // properties of the vertex
   setFlag(QGraphicsItem::ItemIsFocusable);
   setFlag(QGraphicsItem::ItemIsMovable);
   setFlag(QGraphicsItem::ItemIsSelectable);
   setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}


// protected:
// menu options at click
/*void GraphVertex::contextMenuEvent(QGraphicsSceneContextMenuEvent * event) {
   scene()->clearSelection();
   setSelected(true);
//   contextmenu_v->exec(event->scenePos());
}
*/
// moving a vertex moves any attached edge with it
QVariant GraphVertex::itemChange(GraphicsItemChange change
                                 , const QVariant & value) {
   if (change == QGraphicsItem::ItemPositionChange){
      for (GraphEdge * edge : qAsConst(edges))
         edge->resetEdgePosition();
   }

   return value;
}

// enable dynamic provisioning of vertices
void GraphVertex::paint(QPainter * painter
                        , const QStyleOptionGraphicsItem * option
                        , QWidget * widget) {
   Q_UNUSED(option)
   Q_UNUSED(widget)

   // call paint to render (constructor) standard vertex
   QGraphicsEllipseItem::paint(painter, option, widget);

   // font, pen and alignment of vertex id
   painter->setFont(vertexidfont);
   painter->setPen(vertexidpen);
   painter->drawText(vertexboundaryrect, Qt::AlignCenter, QString::number(vertexid));
}


