//
// framework for graph state interaction
//
#include "mainwindow.hpp"

#include <QFileDialog>
#include <QMenuBar>


// public:
MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
{
   createMenus();

   view= new GraphView(this);
   view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
   setCentralWidget(view);
   setWindowTitle(tr("tuQ"));
//   view->set_lattice(15,15);
}


// private:
void MainWindow::createMenus() {
   fileMenu= menuBar()->addMenu(tr("&File"));
   fileMenu->addAction(tr("E&xit"), this, [this](){
      QWidget::close();
   });
}