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


void h_deleteEdge(GraphEdge * edge, QGraphicsScene & scene) {
   // delete GraphEdge from scene
   // pre-condition: target object is type, GraphEdge
   // post-condition: any formerly connected (Graph)vertices are unaffected

   // remove the edge from (vector) alledges of both vertices
   edge->p1vertex->removeEdge(edge);
   edge->p2vertex->removeEdge(edge);

   // back out edge from scene
   scene.removeItem(edge);
}

void h_deleteVertex(GraphVertex & vertex, QGraphicsScene & scene) {
   // delete GraphVertex from scene
   // pre-condition: target object is type, GraphVertex
   // post-condition: all connected (Graph)edges are removed

   // 'alledges' is a copy of container, edges, while removeEdge() executes
   //  against that container...
   QVector<GraphEdge *> copy_edges= *vertex.alledges;

   // remove any and all (Graph)edges connected to vertex
   for (GraphEdge * e : copy_edges) {
      h_deleteEdge(e,scene);
   }
   // back out vertex from scene
   scene.removeItem(&vertex);

   // placeholder: reset IDs?
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

void h_localComplementation(GraphVertex & lcv, QGraphicsScene & scene
                            , QMenu * const menu) {
   // local complementation (LC) applied to in-focus vertex, lcv: all vertices
   // of lcv's neighbourhood not joined by a (graph)edge to be joined by an
   // edge; all vertices of lcv's neighbourhood joined by a (graph)edge to lose
   // that edge.
   // pre-condition: target object is type, GraphVertex
   // post-condition: edges are reconfigured as consistent with LC

   // ABORT LC operation: vertex lcv has <= 1 edge
   if (lcv.alledges->count() < 2)
      return;

   QPointF lcv_pos {lcv.pos()};

   // populate vector of lcv neighbours
   QVector<GraphVertex *> lcNeighbours;
   for (const GraphEdge * e : *lcv.alledges) {
      GraphVertex * marker;
      if (e->p1vertex->pos() == lcv_pos)
         marker= e->p2vertex;
      else
         marker= e->p1vertex;

      if (!lcNeighbours.contains(marker))
         lcNeighbours.push_back(marker);
   }

   // accumulate unique sub-sequences of lcv neighbours
   struct Pair_Neighbours {
      GraphVertex * vertex_1;
      GraphVertex * vertex_2;

      bool operator==(const Pair_Neighbours &rhs) const {
         return (vertex_1 == rhs.vertex_1 && vertex_2 == rhs.vertex_2);
      }
   };
   QVector<Pair_Neighbours> neighbour_sub_sequences {};

   int neighbour_idx {0};
   int neighbours_count {lcNeighbours.count()};

   while (neighbour_idx < neighbours_count) {
      for (int i= neighbour_idx + 1; i < neighbours_count; ++i) {
         // sub-sequence of neighbours
         Pair_Neighbours edge_ref {lcNeighbours[neighbour_idx]
                                   , lcNeighbours[i]};
         // accumulate sub-sequences
         neighbour_sub_sequences.push_back(edge_ref);
      }
      neighbour_idx += 1;
   }

   QVector<Pair_Neighbours> add_edges {};
   QVector<GraphEdge *> delete_edges {};

   for (Pair_Neighbours v_pair : neighbour_sub_sequences) {
      bool p_add_edge {true};
      // operation: DELETE edge, at least one of the vertices of v_pair must
      // have more than one edge; an edge count of one is the edge with lcv
      if (v_pair.vertex_1->alledges->count() > 1){
         for (GraphEdge * edge_match : *v_pair.vertex_1->alledges) {
            if ((edge_match->p1vertex->pos() == v_pair.vertex_2->pos() ||
            edge_match->p2vertex->pos() == v_pair.vertex_2->pos())
            && !delete_edges.contains(edge_match)){
               delete_edges.push_back(edge_match);
               p_add_edge= false;

               // lazy evaluation of matching logic vis-a-vis vertex_2
               continue ;
            }
         }
      }
      else if (v_pair.vertex_2->alledges->count() > 1){
         for (GraphEdge * edge_match : *v_pair.vertex_2->alledges) {
            if ((edge_match->p1vertex->pos() == v_pair.vertex_1->pos() ||
                 edge_match->p2vertex->pos() == v_pair.vertex_1->pos())
                && !delete_edges.contains(edge_match)){
               delete_edges.push_back(edge_match);
               p_add_edge= false;
            }
         }
      }

      // operation: ADD edge
      if (p_add_edge && !add_edges.contains(v_pair))
         add_edges.push_back(v_pair);
   }
   // ADD edge(s)
   for (Pair_Neighbours newEdge : add_edges) {
      auto * e= new GraphEdge(newEdge.vertex_1, newEdge.vertex_2, menu);
      newEdge.vertex_1->addEdge(e);
      newEdge.vertex_2->addEdge(e);
      scene.addItem(e);
   }
   // DELETE edge(s)
   for (GraphEdge * delEdge: delete_edges) {
      h_deleteEdge(delEdge, scene);
   }
}
