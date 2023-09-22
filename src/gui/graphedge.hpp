#ifndef TUQ_GRAPHEDGE_HPP
#define TUQ_GRAPHEDGE_HPP

#include <QGraphicsLineItem>
#include <QPen>

class GraphVertex;

class GraphEdge : public QGraphicsLineItem
{
   QMenu * contextmenu_e {};

   QPen edgecolour {Qt::black, 2};

   GraphVertex * p1v {};
   GraphVertex * p2v {};

public:
   // qgraphicsitem_cast (type), QGraphicsLineItem::Type = 6
   GraphEdge(GraphVertex *, GraphVertex *, QMenu *
             , QGraphicsItem * parent= nullptr);

   const GraphVertex * p1vertex {p1v};
   const GraphVertex * p2vertex {p2v};

   void resetEdgePosition();

protected:

};

#endif //TUQ_GRAPHEDGE_HPP
