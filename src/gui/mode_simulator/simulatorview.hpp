#ifndef TUQ_SIMULATORVIEW_HPP
#define TUQ_SIMULATORVIEW_HPP

#include <fstream>
#include <QGraphicsView>


class SimulatorView : public QGraphicsView
{
Q_OBJECT

   QGraphicsScene * s_scene;

public:
   explicit SimulatorView(QWidget * parent= nullptr);

   void clear_scene() { s_scene->clear(); }
//   void readCircuit(const QString &);

};

#endif //TUQ_SIMULATORVIEW_HPP
