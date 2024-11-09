#ifndef TUQ_SIMULATORVIEW_HPP
#define TUQ_SIMULATORVIEW_HPP

#include "algorithmlattice.hpp"
#include "gates_lattice_set.hpp"
#include "io_circuit.hpp"

#include <fstream>
#include <QGraphicsView>


class SimulatorView : public QGraphicsView
{
   unsigned long colSwapProxy1;
   // quantify a hypothetical lattice underlying Simulator tiles
   ColumnData columnLengths [latticeDim]= {
         ColumnData(0, false), ColumnData(0, false), ColumnData(0, false), ColumnData(0, false), ColumnData(0, false)
         , ColumnData(0, false), ColumnData(0, false), ColumnData(0, false), ColumnData(0, false), ColumnData(0, false)
         , ColumnData(0, false), ColumnData(0, false), ColumnData(0, false), ColumnData(0, false), ColumnData(0, false)
         , ColumnData(0, false), ColumnData(0, false), ColumnData(0, false), ColumnData(0, false), ColumnData(0, false), ColumnData(0, false)};
   unsigned long mStat {1};
   unsigned long nStat {1};
   QString openSign {};
   SignMeasure * p_tileType {};
   bool swapProxy1 {false};
   bool swapProxy2 {false};

   void latticeFromPatterns(unsigned long);

public:
   explicit SimulatorView(QWidget * parent= nullptr);

   AlgorithmLattice * s_scene;

   void openAlgorithm(const QString &);
   void readCircuit(const QString &);
   void saveAlgorithm(const QString &, const unsigned long (&)[latticeDim]) const;
};

#endif //TUQ_SIMULATORVIEW_HPP
