#ifndef TUQ_SIMULATORVIEW_HPP
#define TUQ_SIMULATORVIEW_HPP

#include "algorithmlattice.hpp"

#include <fstream>
#include <QGraphicsView>


class SimulatorView : public QGraphicsView
{
public:
   explicit SimulatorView(QWidget * parent= nullptr);

   AlgorithmLattice * s_scene;

   void clear_scene() { s_scene->clear(); }
//   void readCircuit(const QString &);
   void saveAlgorithm(const QString &, const unsigned int (&)[21]);
};

#endif //TUQ_SIMULATORVIEW_HPP
