#ifndef TUQ_GRAPHVIEW_HPP
#define TUQ_GRAPHVIEW_HPP

#include "gates_lattice_set.hpp"
#include "gui_helpers.hpp"
#include "io_circuit.hpp"

#include <fstream>
#include <QGraphicsView>
#include <QLabel>


class GraphView : public QGraphicsView
{
   Q_OBJECT

   QLabel * clabel {};
   bool cursorState {false};
   QGraphicsScene * scene;
   QGraphicsLineItem * tracer {};

   void setCursorLabel(int);

public:
   explicit GraphView(QWidget *parent= nullptr);

   void clear_scene() { scene->clear(); }
   void openGraph(const QString &);
   void readCircuit(const QString &);
   void saveGraph(const QString &);
   void set_lattice(unsigned long, unsigned long);

protected:
   void keyPressEvent(QKeyEvent *) override;
   void mouseMoveEvent(QMouseEvent *) override;
   void mousePressEvent(QMouseEvent *) override;
   void mouseReleaseEvent(QMouseEvent *) override;
};

#endif //TUQ_GRAPHVIEW_HPP
