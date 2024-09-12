#ifndef TUQ_SIMULATORVIEW_HPP
#define TUQ_SIMULATORVIEW_HPP

#include "algorithmlattice.hpp"
#include "gates_lattice_set.hpp"
#include "io_circuit.hpp"

#include <fstream>
#include <QGraphicsView>


class SimulatorView : public QGraphicsView
{
   QString openSign {};
   SignMeasure * tileType {};

public:
   explicit SimulatorView(QWidget * parent= nullptr);

   AlgorithmLattice * s_scene;

   void openAlgorithm(const QString &);
   void readCircuit(const QString &);
   void saveAlgorithm(const QString &, const unsigned long (&)[21]) const;
};

#endif //TUQ_SIMULATORVIEW_HPP
