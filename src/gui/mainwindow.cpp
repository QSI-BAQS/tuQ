//
// statement of purpose
//

#include "mainwindow.hpp"

#include <QGraphicsView>

// public:
MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
{
   setWindowTitle("tuQ");

   view= new GraphView(this);
   setCentralWidget(view);
//   view->set_lattice(15,15);

}

