//
// specify an edge object
//
#include "graphedge.hpp"
#include "graphvertex.hpp"


// public:
GraphEdge::GraphEdge(GraphVertex * p1vx, GraphVertex * p2vx, QMenu * menu
                     , QGraphicsItem * parent)
   : QGraphicsLineItem(parent), p1v(p1vx), p2v(p2vx)
   , contextmenu_e(menu)
{
   // standard edge: colour, width
   setPen(edgecolour);

   // instantiate the edge; position edge behind its p1 and p2 vertices
   QLineF edge(mapFromItem(p1v, 10, 10)
      , mapFromItem(p2v, 10, 10));
   setLine(edge);
   setZValue(-999);

   // properties of the edge
   setFlag(QGraphicsItem::ItemIsSelectable);
}

void GraphEdge::resetEdgePosition() {
   if (p1v != nullptr && p2v != nullptr){
      QLineF edge(mapFromItem(p1v, 10, 10)
            , mapFromItem(p2v, 10, 10));
      setLine(edge);
   }
}


// protected:
