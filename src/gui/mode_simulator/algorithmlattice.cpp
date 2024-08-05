//
// proxy lattice for (OperatorPalette) patterns
//

#include "algorithmlattice.hpp"
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
   // 'change row' button
   connect(p_operators->changeRow,&QPushButton::clicked
           ,[this](){ changeRow(rowMarker); });

   p_operators->show();
}

// private
void AlgorithmLattice::changeRow(unsigned int * ptr_Row) {
//   *ptr_Row= 1;
   p_operators->setModal(true);
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

