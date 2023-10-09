//
// assorted helper functions
//

#include "gui_helpers.hpp"


// count of items in scene by QGraphicsItem::Type
unsigned long items_count(int item_type, QGraphicsScene * scene) {
   unsigned long counter {1};
   for (QGraphicsItem * item : scene->items()) {
      if (item->type() == item_type)
         counter += 1;
   }

   return counter;
}