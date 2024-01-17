#ifndef TUQ_GUI_HELPERS_HPP
#define TUQ_GUI_HELPERS_HPP

#include "graphedge.hpp"
#include "graphvertex.hpp"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QLineEdit>


void h_deleteEdge(GraphEdge *, QGraphicsScene &);
void h_deleteVertex(GraphVertex &, QGraphicsScene &);
unsigned long h_itemCounter(int, const QGraphicsScene &);
void h_localComplementation(GraphVertex &, QGraphicsScene &, QMenu * const);

#endif //TUQ_GUI_HELPERS_HPP
