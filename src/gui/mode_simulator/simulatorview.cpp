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
   // reset columns counter
   auto n= sizeof(s_scene->columnAtRow) / sizeof(s_scene->columnAtRow[0]);
   memset(s_scene->columnAtRow, 0, n * s_scene->columnAtRow[0]);

   // place all tiles
   int savedRow {};
   int savedCol {};
   QString tileData{inStream.readLine()};

   while (!tileData.isNull()) {
      QStringList tileSpecs= tileData.split(QChar(' '));

      if (tileSpecs.length() == 4){
         openSign= tileSpecs.at(0) % " " % tileSpecs.at(1);
         savedRow= tileSpecs.at(2).toInt();
         savedCol= tileSpecs.at(3).toInt();
      }
      else {
         openSign= tileSpecs.at(0);
         savedRow= tileSpecs.at(1).toInt();
         savedCol= tileSpecs.at(2).toInt();
      }

      // reproduce tile
      tileType= new SignMeasure(openSign);
      tileType->setPos(nodeAddress[savedRow][savedCol]);

      // populate counts of columns by row
      if (openSign.startsWith("CNOT t"))
         s_scene->alignColumns(savedRow, savedRow + 1);
      else
         s_scene->columnAtRow[savedRow] += 1;
//qDebug() << "columnAtRow[" << savedRow << "] =" << s_scene->columnAtRow[savedRow];
      s_scene->addItem(tileType);

      tileData= inStream.readLine();
   }
   loadfile.close();
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

