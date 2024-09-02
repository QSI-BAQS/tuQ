//
// specify simulator view/scene objects
//

#include "simulatorview.hpp"

#include <QDebug>
#include <QFile>
#include <QScrollBar>
#include <QTextStream>


// public:
SimulatorView::SimulatorView(QWidget * parent)
      : QGraphicsView(parent), s_scene(new AlgorithmLattice(this))
{
   // encompass 21 * 21 tiles
   s_scene->setSceneRect(-760,-500,4150,1580);
   setScene(s_scene);

   const qreal x= s_scene->sceneRect().x();
   const qreal y= s_scene->sceneRect().y();

   auto hbar= new QScrollBar(Qt::Horizontal, this);
   setHorizontalScrollBar(hbar);
   hbar->setSliderPosition((int) x - 25);

   auto vbar= new QScrollBar(Qt::Vertical, this);
   setVerticalScrollBar(vbar);
   vbar->setSliderPosition((int) y - 25);
}

void SimulatorView::openAlgorithm(const QString & rfile) {
   QFile loadfile(rfile);

   // read conditions: read-only, text
   if (!loadfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << " file is not open";
      return;
   }

   QTextStream inStream(&loadfile);

   // prepare view
   clear_scene();

   // place all tiles
   QString tileData{inStream.readLine()};

   while (!tileData.isNull()) {
      QStringList tileSpecs= tileData.split(QChar(' '));
      openSign= tileSpecs.at(0);
      qDebug() << openSign;
      int savedRow= tileSpecs.at(1).toInt();
      qDebug() << "savedRow" << savedRow;
      int savedCol= tileSpecs.at(2).toInt();
qDebug() << "savedCol" << savedCol;/*
      // reproduce tile
      tileType= new SignMeasure(openSign);
      tileType->setPos(nodeAddress[savedRow][savedCol]);

      // populate counts of columns by row
      s_scene->columnAtRow[savedRow] += 1;  // debug: s_scene->columnAtRow has same 1 0 0 0 0 problem as saveAlgorithm

      s_scene->addItem(tileType);*/

      tileData= inStream.readLine();
   }/*
   s_scene->p_operators= new OperatorPalette;
   s_scene->p_operators->show();*/
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

   int arraySize= sizeof(latticeColumnsAtRow) / sizeof(latticeColumnsAtRow[0]);
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
         // write: row, column position, as x, y coordinates
         << implicitRow << " " << c
//         << QString::number(pos.x()) << " " << QString::number(pos.y())
         // write: newline
         << "\n";
      }
      implicitRow += 1;
   }
   writefile.flush();
   writefile.close();
}

