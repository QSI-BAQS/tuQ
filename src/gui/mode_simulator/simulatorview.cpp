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

   int arraySize= sizeof(latticeColumnsAtRow) / sizeof(unsigned int);
   int implicitRow {0};
   while (implicitRow < arraySize && latticeColumnsAtRow[implicitRow] != 0) {
      unsigned int columns= latticeColumnsAtRow[implicitRow];

      for (unsigned int c= 0; c < columns; ++c) {
         QPointF pos= nodeAddress[implicitRow][c];
         QGraphicsItem * p_itemAtColumn= s_scene->itemAt(pos,QTransform());
         auto * p_operatorAtColumn= qgraphicsitem_cast<SignMeasure *>(
               p_itemAtColumn);
         QString marker= p_operatorAtColumn->showOperator();

         // write: tile type
         write << marker << " "
         // write: position, as x, y coordinates
         << QString::number(pos.x()) << " " << QString::number(pos.y())
         // write: newline
         << "\n";
      }
      implicitRow += 1;
   }
   writefile.flush();
   writefile.close();
}

