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
   editMenu= nullptr;
   circuitMenu= nullptr;
   graphreadcircuit= nullptr;
   latticeMenu= nullptr;

   createMenus();

   view= new GraphView(this);
   view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
   setCentralWidget(view);
   setWindowTitle(tr("tuQ"));
}


// private:
void MainWindow::createMenus() {
   fileMenu= menuBar()->addMenu(tr("&File"));
   // TO DO: *** shortcut key(s) Ctrl + O ***
   fileMenu->addAction(tr("&Open"), this, [this](){
      openGraphDialog(graphopenfile);
   });
   // TO DO: *** shortcut key(s) Ctrl + S ***
   fileMenu->addAction(tr("&Save"), this, [this](){
      saveGraphDialog(graphsavefile);
   });
   // TO DO: *** shortcut key(s) Ctrl + Q ***
   fileMenu->addAction(tr("E&xit"), this, [this](){
      QWidget::close();
   });

   editMenu= menuBar()->addMenu(tr("&Edit"));
   // TO DO: *** function; shortcut key(s) Ctrl + Z ***
   editMenu->addAction(tr("&Undo"));
   // TO DO: *** shortcut key(s) Ctrl + 0 ***
   editMenu->addAction(tr("Cle&ar Screen"), this, [this]() {
      view->clear_scene();
   });

   circuitMenu= menuBar()->addMenu(tr("&Circuit"));
   // TO DO: *** shortcut key(s) ***
   circuitMenu->addAction(tr("&Read Circuit"), this, [this](){
      readCircuitDialog(graphreadcircuit);
   });

   latticeMenu= menuBar()->addMenu(tr("&Lattice"));
   // TO DO: *** shortcut key(s) ***
   latticeMenu->addAction(tr("A&dd Lattice"), this, [this](){
      addLattice();
   });
}

void MainWindow::addLattice() {
   // create data input Dialog
   // pre-condition: call via MainWindow menu option
   // post-condition: populate menu function, Lattice > Add Lattice

   // TO DO: vanilla Linux includes title bar on dialog?
   auto * dialog= new InputDialog("Add Lattice");

   auto * rowsLineEdit= new QLineEdit(dialog);
   rowsLineEdit->setPlaceholderText("0");
   dialog->form->insertRow(1,"&Rows", rowsLineEdit);

   auto * columnsLineEdit= new QLineEdit(dialog);
   columnsLineEdit->setPlaceholderText("0");
   dialog->form->insertRow(2,"&Columns", columnsLineEdit);

   if(dialog->exec() == QDialog::Accepted){
      unsigned long rows {rowsLineEdit->text().toULong()};
      unsigned long columns {columnsLineEdit->text().toULong()};
      view->setLattice(rows,columns);
   }
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
