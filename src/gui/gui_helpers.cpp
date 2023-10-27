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


void h_deleteEdge(GraphEdge * edge, QGraphicsScene * scene) {
   // delete GraphEdge
   // pre-condition: target object is type, GraphEdge
   // post-condition: target GraphEdge is removed from scene, any formerly
   //   connected (Graph)vertices are unaffected

   // remove the edge from (vector) alledges of both vertices
   edge->p1vertex->removeEdge(edge);
   edge->p2vertex->removeEdge(edge);

   // back out edge from scene
   scene->removeItem(edge);
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

   QPointF lcv_pos {lcv.pos()};

   // populate vector of lcv neighbours
   QVector<GraphVertex *> lcNeighbours;
   for (const GraphEdge * e : *lcv.alledges) {
         if (e->p1vertex->pos() == lcv_pos)
            lcNeighbours.push_back(e->p2vertex);
         else
            lcNeighbours.push_back(e->p1vertex);
   }

   // Vector: GraphEdge for DELETE operation
   QVector<GraphEdge *> d_edges {};

   for (GraphVertex * v : lcNeighbours) {
      for (GraphEdge * e : *v->alledges) {
         QPointF p1v_pos {e->p1vertex->pos()};
         QPointF p2v_pos {e->p2vertex->pos()};
         // edge is not connected to lcv
         if (p1v_pos != lcv_pos && p2v_pos != lcv_pos){
            if (d_edges.isEmpty())
               d_edges.push_back(e);
            else {
               // d_edges contains neither edge nor its inverse
               for (GraphEdge * unique : d_edges) {
                  QPointF p1v_unique {unique->p1vertex->pos()};
                  QPointF p2v_unique {unique->p2vertex->pos()};

                  if (p1v_unique != p1v_pos && p1v_unique != p2v_pos &&
                  p2v_unique != p2v_pos && p2v_unique != p1v_pos
                  )
                     d_edges.push_back(e);
               }
            }
         }
      }
   }

   // Vector: paired neighbour vertices for (edge) ADD operation
   struct addEdge {
      GraphVertex * A;
      GraphVertex * B;
   };
   QVector<addEdge> a_vertices {};

   QPointF vertex_1_pos {};
   QPointF vertex_2_pos {};
   int neighbour{1};

   for (int i= 0; i < lcNeighbours.count() ; ++i) {
      if (neighbour % 2 == 0){
         vertex_2_pos= lcNeighbours[i]->pos();

//         if (lcNeighbours[i-1]->alledges->contains())

      }
      else
         vertex_1_pos= lcNeighbours[i]->pos();

      neighbour += 1;
   }

/*
   // delete edge(s)
   for (auto delEdge : d_edges) {
      h_deleteEdge(delEdge,scene);
   }
   // add edge(s)
   for (auto newEdge : a_vertices) {
      scene.addItem(newEdge);
   }*/
}
