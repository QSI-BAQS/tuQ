#ifndef TUQ_GRAPHVERTEX_HPP
#define TUQ_GRAPHVERTEX_HPP


#include <QGraphicsEllipseItem>
//#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>


class GraphEdge;

class GraphVertex : public QGraphicsEllipseItem
{
   QMenu * contextmenu_v {};

   QVector<GraphEdge *> edges;

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

   const QVector<GraphEdge *> * alledges {& edges};
   const unsigned long * vertexID {& vertexid};

   void addEdge(GraphEdge * edge) { edges.push_back(edge); };

protected:
//   void contextMenuEvent(QGraphicsSceneContextMenuEvent *) override;
   QVariant itemChange(GraphicsItemChange, const QVariant &) override;
   void paint(QPainter *, const QStyleOptionGraphicsItem *
              , QWidget *) override;
};

#endif //TUQ_GRAPHVERTEX_HPP