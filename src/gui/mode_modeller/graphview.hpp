#ifndef TUQ_GRAPHVIEW_HPP
#define TUQ_GRAPHVIEW_HPP

#include "gates_lattice_set.hpp"
#include "modeller_helpers.hpp"
#include "io_circuit.hpp"

#include <fstream>
#include <QGraphicsView>
#include <QLabel>

// <QGraphicsView>
#pragma once


class GraphView : public QGraphicsView
{
   Q_OBJECT

   QLabel * clabel {};
   bool cursorState {false};
   QMenu * edgemenu {};
   QGraphicsScene * scene;
   QGraphicsLineItem * tracer {};
   QMenu * vertexmenu {};
   GraphVertex * vertex1_X {};
   QVector<GraphVertex *> vertex1_X_neighbours {};

   void createElementMenus(QGraphicsScene *);
   void setCursorLabel(int);

public:
   explicit GraphView(QWidget * parent= nullptr);

   void clear_scene() { scene->clear(); }
   void openGraph(const QString &);
   void readCircuit(const QString &);
   void saveGraph(const QString &);
   void setLattice(unsigned long, unsigned long);

protected:
   void keyPressEvent(QKeyEvent *) override;
   void mouseMoveEvent(QMouseEvent *) override;
   void mousePressEvent(QMouseEvent *) override;
   void mouseReleaseEvent(QMouseEvent *) override;
};

#endif //TUQ_GRAPHVIEW_HPP
