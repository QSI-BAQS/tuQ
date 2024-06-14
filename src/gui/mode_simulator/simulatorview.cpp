//
// specify simulator view/scene objects
//

#include "simulatorview.hpp"


// public:
SimulatorView::SimulatorView(QWidget * parent)
      : QGraphicsView(parent), s_scene(new QGraphicsScene(this))
{
   // '... one unit on the scene is represented by one pixel on the screen.'
   // *** ~[121, 121] accessible at this sceneRect ***
   /* FIX: setSceneRect has to be consistent between this and setLattice otherwise
      lattice created in one set of coordinates do not show up in the other set */
   s_scene->setSceneRect(-2500,-2500,11000,11000);

   setScene(s_scene);

}

// copy-and-paste from GraphView, requires <QDebug>
//void SimulatorView::readCircuit(const QString & cjson);
