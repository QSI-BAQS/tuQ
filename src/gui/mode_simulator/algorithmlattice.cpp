//
// proxy lattice for (OperatorPalette) patterns
//

#include "algorithmlattice.hpp"


// public
AlgorithmLattice::AlgorithmLattice(QWidget * parent)
      : QGraphicsScene(parent)
{
   setSceneRect(latticeDims);

   p_operatorType= nullptr;
   p_operators= new OperatorPalette();

   p_initialise00= new SignMeasure(ket0);
   p_initialise00->setPos(nodeAddress[0][0]);
   addItem(p_initialise00);

   columnAtRow[*rowMarker] += 1;
   lastInsert= nodeAddress[0][0];

   // method by (p_operators) button id, excluding button 'add row'
   connect(p_operators->measurement_buttons,&QButtonGroup::idClicked
           ,[this](const int id){
      placeOperator(p_operators->measurements[id], columnAtRow[*rowMarker]);
   });
   connect(p_operators->pattern_buttons,&QButtonGroup::idClicked
           ,[this](const int id){ placeOperator(p_operators->patterns[id]
           , columnAtRow[*rowMarker]); });
   // 'add row' button
   connect(p_operators->p_addRow, &QPushButton::clicked, [this](){
      addRow(); });
   // 'switch rows' form
   connect(p_operators->possibleRows
           ,QOverload<int>::of(&QComboBox::highlighted)
           ,[this](int index){ *rowMarker= index; });

   p_operators->show();
}

// private
void AlgorithmLattice::placeOperator(QString sign, unsigned int column) {
//   instantiate and place graph operators at (simulator_helpers) nodeAddress
//   coordinates
//   pre-condition: user clicks any of the 'measurement bases' or 'measurement
//   patterns' buttons
//   post-condition: traversable linked list of 1+ SignMeasure objects

   // format the lattice marker of argument 'sign'
   p_operatorType= new SignMeasure(sign);

   // TO DO: finesse for addRow operations
   // linked list of SignMeasure objects
   if (itemAt(lastInsert,QTransform())){
      QGraphicsItem * p_operatorAtLastInsert= itemAt(lastInsert,QTransform());
      auto * p_lastOperator=
            qgraphicsitem_cast<SignMeasure *>(p_operatorAtLastInsert);
      p_operatorType->p_CZ= p_lastOperator;
   }

   // place the operator
   if (sign == "CNOT t" % QChar(0x2191)){   // operator, CNOT t upwards arrow
      if (*rowMarker > 0){
         unsigned int rowCNOTUpwardsArrow= *rowMarker - 1;

         prepareOperator(*p_operatorType,rowCNOTUpwardsArrow, column);
         // advance column count at adjacent, up row
         columnAtRow[*rowMarker] += 1;
      }
      else
         // CNOT t upwards arrow does not insert a row!!
         return;
   }
   else if (sign == "CNOT t" % QChar(0x2193)){   // operator, CNOT t downwards arrow
      unsigned int controlRowColumn= columnAtRow[*rowMarker];

      // edge case: three consecutive CNOTs as Swap operator proxy
      if (p_operatorType->p_CZ->showOperator() == "CNOT t" % QChar(0x2191)){
         if (controlRowColumn > 2){
            prepareOperator(*p_operatorType, *rowMarker, column);
            // align column counts of control and target rows
            columnAtRow[*maxRowMarker]= controlRowColumn + 1;
         }
      }
      else {
         prepareOperator(*p_operatorType, *rowMarker, column);
         addRow();
         // align column counts of control and target rows
         columnAtRow[*rowMarker]= controlRowColumn + 1;
      }
   }
   else   // non-CNOT operators
      prepareOperator(*p_operatorType, *rowMarker, column);

   addItem(p_operatorType);
   p_operators->setModal(true);
}

void AlgorithmLattice::prepareOperator(SignMeasure & graphOperator
                                       , unsigned int row
                                       , unsigned int column) {
// meet placement requirements common to CNOT/non-CNOT operators
// pre-condition: subsidiary to method, placeOperator()
//   post-condition: N/A

   // (set)Pos = parent coordinates else, scene coordinates
   graphOperator.setPos(nodeAddress[row][column]);
   // retain nodeAddress[...][column] of current row
   columnAtRow[row] += 1;

   lastInsert= nodeAddress[row][column];
}

void AlgorithmLattice::addRow() {
//   add a row in response to pre-conditions
//   pre-condition: either
//      - user clicks OperatorPalette button, 'Add Row'; OR
//      - user clicks OperatorPalette button, 'CNOT t downwards arrow',
//   but not both.
//   post-condition: N/A
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

   // advance column counter at inserted row
   columnAtRow[*rowMarker] += 1;
}
