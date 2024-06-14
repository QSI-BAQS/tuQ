#ifndef TUQ_MODELLER_HELPERS_HPP
#define TUQ_MODELLER_HELPERS_HPP

#include "graphedge.hpp"
#include "graphvertex.hpp"

#include <QGraphicsItem>
#include <QGraphicsScene>


void h_deleteEdge(GraphEdge *, QGraphicsScene &);
void h_deleteVertex(GraphVertex &, QGraphicsScene &);
unsigned long h_itemCounter(int, const QGraphicsScene &);
void h_localComplementation(GraphVertex &, QGraphicsScene &, QMenu *);

#endif //TUQ_MODELLER_HELPERS_HPP
