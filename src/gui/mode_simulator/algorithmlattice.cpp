//
// proxy lattice for (OperatorPalette) patterns
//

#include "algorithmlattice.hpp"
#include "simulator_helpers.hpp"


// public
AlgorithmLattice::AlgorithmLattice(QWidget * parent)
      : QGraphicsScene(parent)
{
   setSceneRect(latticeDims);

   p_operators= new OperatorPalette();

   // method by (p_operators) button id, excluding button 'add row'
   connect(p_operators->measurement_buttons,&QButtonGroup::idClicked
           ,[this](const int id){
      placeOperator(p_operators->measurements[id], columnAtRow[*rowMarker]);
   });
   connect(p_operators->pattern_buttons,&QButtonGroup::idClicked
           ,[this](const int id){ placeOperator(p_operators->patterns[id]
           , columnAtRow[*rowMarker]); });
   // 'add row' button
   connect(p_operators->p_addRow, &QPushButton::clicked, this
           , &AlgorithmLattice::addRow);
   // 'switch rows' form
   connect(p_operators->possibleRows
           ,QOverload<int>::of(&QComboBox::highlighted)
           ,[this](int index){ *rowMarker= index; });

   p_operators->show();
}

// private
void AlgorithmLattice::addRow() {
   *maxRowMarker += 1;

   // update the QComboBox, 'switch rows'
   auto rowID= (int) *maxRowMarker;
   auto rowValue= QString::number(*maxRowMarker);
   p_operators->possibleRows->insertItem(rowID,rowValue);
   // reset 'switch rows' display to the added row
   p_operators->possibleRows->setCurrentIndex(rowID);

   // align nodeAddress[row][...] with added row
   unsigned int nowRowMarker= *maxRowMarker;
   *rowMarker= nowRowMarker;
}

void AlgorithmLattice::placeOperator(QString sign, unsigned int column) {
   // format sign's lattice marker
   p_operatorType= new SignMeasure(sign);

   // (set)Pos = parent coordinates else, scene coordinates
   if (items().isEmpty())
      p_operatorType->setPos(nodeAddress[0][0]);
   else if (!items().isEmpty())
      p_operatorType->setPos(nodeAddress[*rowMarker][column]);

   addItem(p_operatorType);

   // retain nodeAddress[...][column] of current row
   columnAtRow[*rowMarker] += 1;

   // clear node at row beneath placed CNOT
   if (sign == "CNOT")
      columnAtRow[*rowMarker + 1] += 1;

   p_operators->setModal(true);
}

