#ifndef TUQ_GRAPHEDGE_HPP
#define TUQ_GRAPHEDGE_HPP

#include <QGraphicsLineItem>
#include <QPen>

class GraphVertex;

class GraphEdge : public QGraphicsLineItem
{
   QMenu * contextmenu_e {};

   QPen edgecolour {Qt::black, 2};

public:
   // qgraphicsitem_cast (type), QGraphicsLineItem::Type = 6
   GraphEdge(GraphVertex *, GraphVertex *, QMenu *
             , QGraphicsItem * parent= nullptr);

   GraphVertex * p1vertex {};
   GraphVertex * p2vertex {};

   void resetEdgePosition();

protected:

};

#endif //TUQ_GRAPHEDGE_HPP
