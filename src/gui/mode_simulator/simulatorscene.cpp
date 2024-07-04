//
// proxy lattice for (OperatorPalette) patterns
//

#include "simulatorscene.hpp"


// public
AlgorithmLattice::AlgorithmLattice(QWidget * parent)
      : QGraphicsScene(parent)
{
//   setMouseTracking(true);
   p_operators= new OperatorPalette();

   // method by (p_operators) button id, excluding button 'change row'
   connect(p_operators->measurement_buttons,&QButtonGroup::idClicked, this
           ,&AlgorithmLattice::measurementsID);
   connect(p_operators->pattern_buttons,&QButtonGroup::idClicked, this
           ,&AlgorithmLattice::patternsID);
   // 'change row' button
   connect(p_operators->changeRow,&QPushButton::clicked,this
           ,&AlgorithmLattice::changeRow);

   p_operators->show();
}

// private
void AlgorithmLattice::changeRow() {
   p_operators->setModal(true);
}

void AlgorithmLattice::measurementsID(int id) {
   QString measurement= p_operators->measurements[id];
   auto signXYZ= new SignMeasure(measurement);

   signXYZ->mapToParent(-150, -150);
   addItem(signXYZ);

   p_operators->setModal(true);
}

void AlgorithmLattice::patternsID(int id) {
   QString pattern= p_operators->patterns[id];
   placeOperator(pattern);
}

void AlgorithmLattice::placeOperator(QString sign) {
   // format the sign's lattice marker
   p_operatorType= new QGraphicsSimpleTextItem;
   p_operatorType->setPen(QPen(Qt::blue));
   p_operatorType->setFont(QFont("Times New Roman", 24));
   p_operatorType->setText(sign);

   p_operatorType->mapToParent(-150,-150);
   addItem(p_operatorType);

   p_operators->setModal(true);
}

