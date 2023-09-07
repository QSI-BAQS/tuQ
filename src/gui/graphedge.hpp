#ifndef TUQ_GRAPHEDGE_HPP
#define TUQ_GRAPHEDGE_HPP

#include <QGraphicsLineItem>
#include <QPen>

class GraphVertex;

class GraphEdge : public QGraphicsLineItem
{
   QPen edgecolour {Qt::black, 2};
   GraphVertex * p1vertex {};
   GraphVertex * p2vertex {};

public:
   GraphEdge(GraphVertex *, GraphVertex *, QGraphicsItem * parent= nullptr);

   GraphVertex * p1v() const { return p1vertex; };
   GraphVertex * p2v() const  { return p2vertex; };

   void resetEdgePosition();
};

#endif //TUQ_GRAPHEDGE_HPP
