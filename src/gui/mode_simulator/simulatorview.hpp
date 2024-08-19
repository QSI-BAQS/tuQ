#ifndef TUQ_SIMULATORVIEW_HPP
#define TUQ_SIMULATORVIEW_HPP

#include "algorithmlattice.hpp"

#include <fstream>
#include <QByteArray>
#include <QGraphicsView>


class SimulatorView : public QGraphicsView
{
   AlgorithmLattice * s_scene;
   QByteArray s_algorithm;
   QByteArray * const p_readAlgorithm= & s_algorithm;

public:
   explicit SimulatorView(QWidget * parent= nullptr);

   void clear_scene() { s_scene->clear(); }
//   void readCircuit(const QString &);
};

#endif //TUQ_SIMULATORVIEW_HPP
