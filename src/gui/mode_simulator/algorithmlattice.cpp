//
// proxy lattice for (OperatorPalette) patterns
//

#include "algorithmlattice.hpp"
#include "simulator_helpers.hpp"
//#include <QDebug>

// public
AlgorithmLattice::AlgorithmLattice(QWidget * parent)
      : QGraphicsScene(parent)
{
   setSceneRect(latticeDims);
//   setMouseTracking(true);
   p_operators= new OperatorPalette();

   // method by (p_operators) button id, excluding button 'change row'
   connect(p_operators->measurement_buttons,&QButtonGroup::idClicked
           ,[this](const int id){
      placeOperator(p_operators->measurements[id], columnMarker);
   });
   connect(p_operators->pattern_buttons,&QButtonGroup::idClicked
           ,[this](const int id){ placeOperator(p_operators->patterns[id]
           , columnMarker); });
   // 'add row' button
   connect(p_operators->p_addRow, &QPushButton::clicked
           ,[this](){ addRow(0); });
   // 'switch rows' form
   connect(p_operators->possibleRows
           ,QOverload<int>::of(&QComboBox::highlighted)
           ,[this](int index){ *rowMarker= index; });   // this needs a function: [...][column] is wrong

   p_operators->show();
}

// private
void AlgorithmLattice::addRow(unsigned int columnStart) {
   *maxRowMarker += 1;

   // update the QComboBox, 'switch rows'
   auto rowID= (int) *maxRowMarker;
   auto rowValue= QString::number(*maxRowMarker);
   p_operators->possibleRows->insertItem(rowID,rowValue);
   // reset row displayed in 'switch rows'
   p_operators->possibleRows->setCurrentIndex(rowID);

   // align nodeAddress[row][...] with added row
   unsigned int nowRowMarker= *maxRowMarker;
   *rowMarker= nowRowMarker;
   // set nodeAddress[...][column] of added row
   *columnMarker= columnStart;
}

void AlgorithmLattice::placeOperator(QString sign, unsigned int * ptr_Column) {
   // format sign's lattice marker
   p_operatorType= new SignMeasure(sign);

   // (set)Pos = parent coordinates else, scene coordinates
   if (items().isEmpty())
      p_operatorType->setPos(nodeAddress[0][0]);
   else if (!items().isEmpty())
      p_operatorType->setPos(nodeAddress[*rowMarker][*ptr_Column]);
   addItem(p_operatorType);
   *ptr_Column += 1;
//   qDebug() << p_operatorType->pos() << ", " << latticeDims;

   p_operators->setModal(true);
}

