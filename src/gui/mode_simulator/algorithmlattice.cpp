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

   p_initialiseRow= new SignMeasure(ket0);
   p_initialiseRow->setPos(nodeAddress[0][0]);
   addItem(p_initialiseRow);

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
      prepareRow();
      columnAtRow[*rowMarker] += 1; });
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
      SignMeasure * p_lastOperator=
            qgraphicsitem_cast<SignMeasure *>(p_operatorAtLastInsert);
      p_operatorType->p_CZ= p_lastOperator;
   }

   // place the operator
      // operator, CNOT t upwards arrow
   if (sign == "CNOT t" % QChar(0x2191)){
      if (*rowMarker > 0){
         unsigned int rowCNOTUpwardsArrow= *rowMarker - 1;

         // (set)Pos = parent coordinates else, scene coordinates
         p_operatorType->setPos(nodeAddress[rowCNOTUpwardsArrow][column]);
         columnAtRow[rowCNOTUpwardsArrow] += 1;
         columnAtRow[*rowMarker] += 1;

         lastInsert= nodeAddress[rowCNOTUpwardsArrow][column];
      }
      else
         // CNOT t upwards arrow does not insert a row!!
         return;
   }
   else {   // all other operators
      p_operatorType->setPos(nodeAddress[*rowMarker][column]);
      // retain nodeAddress[...][column] of current row
      columnAtRow[*rowMarker] += 1;

      lastInsert= nodeAddress[*rowMarker][column];
   }

   // condition = CNOT t downwards arrow
   if (sign == "CNOT t" % QChar(0x2193)){
      unsigned int controlRowColumn= columnAtRow[*rowMarker];
      prepareRow();   // TO DO: tweak to allow third CNOT of swap proxy
      columnAtRow[*rowMarker]= controlRowColumn;
   }

   addItem(p_operatorType);

   p_operators->setModal(true);
}

void AlgorithmLattice::prepareRow() {
//   meet requirements common to addRow() and placeOperator() to prepare a
//   matrix row
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
}
