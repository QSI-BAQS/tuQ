//
// assorted helper functions
//

#include "gui_helpers.hpp"


unsigned long h_item_counter(int item_type, QGraphicsScene * scene) {
   // count of items in scene by QGraphicsItem::Type
   // pre-condition: GraphVertex added to scene by GraphView::mousePressEvent
   // post-condition: counter assigned to vertexid of latest GraphVertex

   unsigned long counter {1};
   for (QGraphicsItem * item : scene->items()) {
      if (item->type() == item_type)
         counter += 1;
   }

   return counter;
}


void h_localComplementation(GraphVertex * lcv) {
   // local complementation (LC) applied to in-focus vertex j: all vertices of
   // j's neighbourhood not joined by a (graph)edge to gain an edge; all
   // vertices of j's neighbourhood joined by a (graph)edge to lose an edge.
   // pre-condition: target object is type, GraphVertex
   // post-condition: edges are reconfigured as consistent with LC

   // LC operation: vertex j has <= 1 edge
   if (lcv->alledges->count() < 2)
      return ;
   // LC operation: vertex j has > 1 edge
   else {}
}