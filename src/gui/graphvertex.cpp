//
// statement of purpose
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


// protected:
/*void GraphVertex::contextMenuEvent(QGraphicsSceneContextMenuEvent * event) {
   scene()->clearSelection();
   setSelected(true);
//   contextmenu_v->exec(event->scenePos());
}*/