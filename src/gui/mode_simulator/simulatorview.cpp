//
// specify simulator view/scene objects
//

#include "simulatorview.hpp"


// public:
SimulatorView::SimulatorView(QWidget * parent)
      : QGraphicsView(parent), s_scene(new AlgorithmLattice(/*p_readAlgorithm
                                                            ,*/ this))
{
   // '... one unit on the scene is represented by one pixel on the screen.'
   // *** ~[121, 121] accessible at this sceneRect ***

   setScene(s_scene);

}

// copy-and-paste from GraphView, requires <QDebug>
//void SimulatorView::readCircuit(const QString & cjson);
