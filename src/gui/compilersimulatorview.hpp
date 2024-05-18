#ifndef TUQ_COMPILERSIMULATORVIEW_HPP
#define TUQ_COMPILERSIMULATORVIEW_HPP

#include "gates_lattice_set.hpp"
#include "gui_helpers.hpp"
#include "io_circuit.hpp"

#include <fstream>
#include <QGraphicsView>


class CompilerSimulatorView : public QGraphicsView
{
   Q_OBJECT

   QGraphicsScene * scene;

public:
   explicit CompilerSimulatorView(QWidget * parent= nullptr);

   void clear_scene() { scene->clear(); }
   void readCircuit(const QString &);

};

#endif //TUQ_COMPILERSIMULATORVIEW_HPP
