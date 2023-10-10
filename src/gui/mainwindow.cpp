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
   fileMenu= nullptr;
   graphopenfile= nullptr;
   graphsavefile= nullptr;
   circuitMenu= nullptr;
   graphreadcircuit= nullptr;

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
   fileMenu->addAction(tr("&Open"), this, [this](){
      openGraphDialog(graphopenfile);
   });
   fileMenu->addAction(tr("&Save"), this, [this](){
      saveGraphDialog(graphsavefile);
   });
   fileMenu->addAction(tr("E&xit"), this, [this](){
      QWidget::close();
   });

   circuitMenu= menuBar()->addMenu(tr("&Circuit"));
   circuitMenu->addAction(tr("&Read Circuit"), this, [this](){
      readCircuitDialog(graphreadcircuit);
   });
}

void MainWindow::openGraphDialog(const QString * openfile) {
   QString file_name= QFileDialog::getOpenFileName(this, tr("Open File"),""
         ,tr("Text files (*.txt)"));
   openfile= &file_name;

   // handle 'cancel' at Dialog box
   if (openfile->isEmpty())
      return ;
   else
      view->openGraph(*openfile);
}

void  MainWindow::readCircuitDialog(const QString * circuitfile) {
   QString file_name= QFileDialog::getOpenFileName(this, tr("Read Circuit"),""
         ,tr("Json files (*.json)"));

   circuitfile= &file_name;

   // handle 'cancel' at Dialog box
   if (circuitfile->isEmpty())
      return ;
   else
      view->readCircuit(*circuitfile);
}

void MainWindow::saveGraphDialog(const QString * savefile) {
   QString file_name= QFileDialog::getSaveFileName(this, tr("Save File"),""
                                                   ,tr("Text files (*.txt)"));
   // QFileDialog.setDefaultSuffix() does not work
   if (!file_name.endsWith(".txt"))
      file_name.append(".txt");

   savefile= &file_name;

   // handle 'cancel' at Dialog box
   if (savefile->isEmpty())
      return ;
   else
      view->saveGraph(*savefile);
}
