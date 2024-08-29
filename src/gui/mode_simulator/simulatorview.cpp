//
// specify simulator view/scene objects
//

#include "simulatorview.hpp"

#include <QDebug>
#include <QFile>
//#include <QScrollBar>
#include <QTextStream>


// public:
SimulatorView::SimulatorView(QWidget * parent)
      : QGraphicsView(parent), s_scene(new AlgorithmLattice(this))
{
   // '... one unit on the scene is represented by one pixel on the screen.'
   // *** ~[121, 121] accessible at this sceneRect ***

   setScene(s_scene);

}

// copy-and-paste from GraphView, requires <QDebug>
//void SimulatorView::readCircuit(const QString & cjson);

// write instructions, format .txt
void SimulatorView::saveAlgorithm(const QString & wfile
                                  , const unsigned int (&latticeColumnsAtRow)[21]) {
   QFile writefile(wfile);

   // save conditions: write-only, text
   if (!writefile.open(QIODevice::WriteOnly | QIODevice::Text)){
      qDebug() << " file is not open";
      return ;
   }

   QTextStream write(&writefile);

   for (unsigned int c : latticeColumnsAtRow) {
      qDebug() << "I'll get back to you";
   }

}



