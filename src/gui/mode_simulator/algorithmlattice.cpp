//
// proxy lattice for (OperatorPalette) patterns
//

#include "algorithmlattice.hpp"


// public
AlgorithmLattice::AlgorithmLattice(/*QByteArray * const pt_patterns
                                   ,*/ QWidget * parent)
      : QGraphicsScene(parent)//, localBuffer(pt_patterns)
{
   setSceneRect(latticeDims);

   p_operators= new OperatorPalette();

   p_initialiseRow= new SignMeasure(ket0);
   p_initialiseRow->setPos(nodeAddress[0][0]);
   addItem(p_initialiseRow);
   columnAtRow[*rowMarker] += 1;

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

   // initialise the new row
   p_initialiseRow= new SignMeasure(ket0);
   p_initialiseRow->setPos(nodeAddress[*rowMarker][0]);
   addItem(p_initialiseRow);
   columnAtRow[*rowMarker] += 1;
}

void AlgorithmLattice::placeOperator(QString sign, unsigned int column) {
   // format sign's lattice marker
   p_operatorType= new SignMeasure(sign);
/*
   // write sign to buffer
   p_writeAlgorithm->open(QBuffer::WriteOnly);
   p_writeAlgorithm->write(sign.toUtf8());
   p_writeAlgorithm->close();
*/
   // (set)Pos = parent coordinates else, scene coordinates
   p_operatorType->setPos(nodeAddress[*rowMarker][column]);
   // retain nodeAddress[...][column] of current row
   columnAtRow[*rowMarker] += 1;

   // move this logic into a helper function, inc. rendering the control and
   // target rows (p_writeAlgorithm) and text (signmeasure.cpp)
   if (sign == "CNOT"){
      // clear node at row beneath placed CNOT
      columnAtRow[*rowMarker + 1] += 1;
   }

   addItem(p_operatorType);

   p_operators->setModal(true);
}

