#ifndef GRAPHVERTEX_HPP
#define GRAPHVERTEX_HPP

#include "graphview.hpp"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QMenu>
//#include <QGraphicsSceneContextMenuEvent>
#include <QPainter>


class GraphEdge;

class GraphVertex : public QGraphicsEllipseItem
{
   QMenu * contextmenu_v {};

   // vertex data
   QSizeF radius {45,45};
   QPointF topleft {0,0};
   QRectF vertexboundaryrect {topleft, radius};

   // vertex rendering
   QPen vertexcircumferencepen {Qt::black, 2};
   QBrush vertexfill {QColor::fromRgb(245,245,245)};   // 'white smoke'

   unsigned long vertexid {};
   QFont vertexidfont {"SansSerif", 8, QFont::Normal};
   QPen vertexidpen {Qt::darkBlue, 1};

public:
   // qgraphicsitem_cast (type), QGraphicsEllipseItem::Type = 4
   explicit GraphVertex(QMenu *, unsigned long vid= 0
         , QGraphicsItem * parent= nullptr);

protected:
//   void contextMenuEvent(QGraphicsSceneContextMenuEvent *) override;
   void paint(QPainter *, const QStyleOptionGraphicsItem *
              , QWidget *) override;
};

#endif // GRAPHVERTEX_HPP