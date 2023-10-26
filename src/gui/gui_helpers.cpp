//
// assorted helper functions
//
#include "gui_helpers.hpp"

#include <QDialogButtonBox>
#include <QLabel>
#include <QDialog>

// public:
InputDialog::InputDialog(QString menu_function, QWidget * parent)
   : QDialog(parent), dialog_type(menu_function), form(new QFormLayout(this))
{
   form->addRow(new QLabel(dialog_type));

   auto * buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok
         | QDialogButtonBox::Cancel,Qt::Horizontal, this);
   form->addRow(buttonBox);

   QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
   QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}


unsigned long h_item_counter(int item_type, const QGraphicsScene & scene) {
   // count of items in scene by QGraphicsItem::Type
   // pre-condition: GraphVertex added to scene by GraphView::mousePressEvent
   // post-condition: counter assigned to vertexid of latest GraphVertex

   unsigned long counter {1};
   for (QGraphicsItem * item : scene.items()) {
      if (item->type() == item_type)
         counter += 1;
   }

   return counter;
}

void h_localComplementation(GraphVertex & lcv, QGraphicsScene & scene) {
   // local complementation (LC) applied to in-focus vertex, lcv: all vertices
   // of lcv's neighbourhood not joined by a (graph)edge to be joined by an
   // edge; all vertices of lcv's neighbourhood joined by a (graph)edge to lose
   // that edge.
   // pre-condition: target object is type, GraphVertex
   // post-condition: edges are reconfigured as consistent with LC

   // ABORT LC operation: vertex lcv has <= 1 edge
   if (lcv.alledges->count() < 2)
      return ;

   // populate vector of lcv neighbours
   QVector<GraphVertex *> lcNeighbours;
   for (const GraphEdge * e : *lcv.alledges) {
         if (e->p1vertex->pos() == lcv.pos())
            lcNeighbours.push_back(e->p2vertex);
         else
            lcNeighbours.push_back(e->p1vertex);
   }

   // 1. ADD edges {scene->addItem(e);}; 2. DELETE edges
   // *** need scene for addItem() ***
}
