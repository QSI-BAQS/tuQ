#ifndef GRAPHVERTEX_HPP
#define GRAPHVERTEX_HPP
#pragma once

#include "graphview.hpp"

#include <QDebug>
#include <QGraphicsEllipseItem>
//#include <QGraphicsSceneContextMenuEvent>
//#include <QMenu>
#include <QPainter>

//class GraphEdge;

class GraphVertex : public QGraphicsEllipseItem
{
// 'class members are private by default'
   QMenu * contextmenu_v {};

   // vertex data
   QSizeF radius {45,45};
   QPointF xy {0,0};
   QRectF vertexboundaryrect {xy, radius};

   // vertex rendering
   QPen vertexcircumferencepen {Qt::black, 2};
   QBrush vertexfill {QColor::fromRgb(245,245,245)};   // 'white smoke'

   unsigned long vertexid {};
   QFont vertexidfont {"SansSerif", 8, QFont::Normal};
   QPen vertexidpen {Qt::darkBlue, 1};


// 'keep interfaces minimal'
public:
   explicit GraphVertex(/*QMenu *,*/ unsigned long vid= 0
         , QGraphicsItem * parent= nullptr);


// 'keep interfaces minimal'
protected:
//   void contextMenuEvent(QGraphicsSceneContextMenuEvent *) override;
   void paint(QPainter *, const QStyleOptionGraphicsItem *
              , QWidget *) override;
};

#endif // GRAPHVERTEX_HPP