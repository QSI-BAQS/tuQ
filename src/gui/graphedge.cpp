//
// statement of purpose
//

#include "graphedge.hpp"
#include "graphvertex.hpp"


// public:
GraphEdge::GraphEdge(GraphVertex * p1v, GraphVertex * p2v, QMenu * menu
                     , QGraphicsItem *parent)
   : QGraphicsLineItem(parent), p1vertex(p1v), p2vertex(p2v)
   , contextmenu_e(menu)
{
   // standard edge: colour, width
   setPen(edgecolour);

   // instantiate the edge; position edge behind its p1 and p2 vertices
   QLineF edge(mapFromItem(p1vertex, 10, 10)
      , mapFromItem(p2vertex, 10, 10));
   setLine(edge);
   setZValue(-999);

   // properties of the edge
   setFlag(QGraphicsItem::ItemIsSelectable);
}

void GraphEdge::resetEdgePosition() {
   if (p1vertex != NULL && p2vertex != NULL){
      QLineF edge(mapFromItem(p1vertex, 10, 10)
            , mapFromItem(p2vertex, 10, 10));
      setLine(edge);
   }
}


// protected:
