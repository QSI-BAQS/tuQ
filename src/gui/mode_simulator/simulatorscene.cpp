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
// connect(settings->buttons[0],&QPushButton::clicked,this, &MainWindow::setModeller);
//   connect(p_operators->pattern_buttons[0])

   p_operators->show();
//   ptest.setPos(150,300);

}
