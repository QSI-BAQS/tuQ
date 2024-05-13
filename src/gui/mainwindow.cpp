//
// framework for graph state interaction
//
#include "mainwindow.hpp"

#include <QFileDialog>
#include <QMenuBar>
#include <QRegExpValidator>


// public:
MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
{
   setActions();
   createMenus();

   settings= new GraphSelect();
   // Q2Graph settings, 'Modeller'
   connect(settings->buttons[0],&QPushButton::clicked,this,&MainWindow::modellerMenu);
   // Q2Graph settings, 'Simulator'
   connect(settings->buttons[1],&QPushButton::clicked,this,&MainWindow::simulatorMenu);
   // Q2Graph settings, 'Compiler'
   connect(settings->buttons[2],&QPushButton::clicked,this,&MainWindow::compilerMenu);
   // Q2Graph settings, 'Exit Q2Graph'
   connect(settings->buttons[3],&QPushButton::clicked, this,&MainWindow::exitButton);

   settings->setModal(true);   // prevent a user from bypassing 'settings'
   settings->show();

   view= new GraphView(this);
   view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
   setCentralWidget(view);
   setWindowTitle(tr("Q2Graph"));
}

// private:
void MainWindow::addLattice() {
   // create input Dialog, positive integers only
   // pre-condition: call via MainWindow menu option
   // post-condition: populate menu function, Lattice > Add Lattice

   // TO DO: vanilla Linux includes title bar on dialog?
   auto * dialog= new InputDialog("Add Lattice");

   // "Rows" and "Columns" QLineEdits
   QRegExp positive_integer {"(0|[1-9][0-9]+)"};

   auto * rowsLineEdit= new QLineEdit(dialog);
   rowsLineEdit->setValidator(new QRegExpValidator(positive_integer));
   rowsLineEdit->setPlaceholderText("0");
   dialog->form->insertRow(1,"&Rows", rowsLineEdit);

   auto * columnsLineEdit= new QLineEdit(dialog);
   columnsLineEdit->setValidator(new QRegExpValidator(positive_integer));
   columnsLineEdit->setPlaceholderText("0");
   dialog->form->insertRow(2,"&Columns", columnsLineEdit);

   if (dialog->exec() == QDialog::Accepted){
      // QLineEdit values set at QDialog::Accepted
      unsigned long rows= rowsLineEdit->text().toULong();
      unsigned long columns= columnsLineEdit->text().toULong();

      // edge case: one input value = 0 but other input value > 0
      if ((rows == 0 && columns > 0) || (rows > 0 && columns == 0))
         view->setLattice(0,0);
      else
         view->setLattice(rows, columns);
   }
}

void MainWindow::compilerMenu() {
   // 'grey out' menu items
   a_addGate->setEnabled(false);
   a_addLattice->setEnabled(false);
   a_openAlgorithm->setEnabled(false);
   a_saveAlgorithm->setEnabled(false);
   a_saveAs->setEnabled(false);

   settings->close();   // close dialog
}

void MainWindow::createMenus() {
   fileMenu= menuBar()->addMenu(tr("&File"));
   fileMenu->addAction(a_openGraph);
   fileMenu->addAction(a_saveGraph);
   fileMenu->addAction(a_saveAs);

   fileMenu->addSeparator();
   fileMenu->addAction(a_openAlgorithm);
   fileMenu->addAction(a_saveAlgorithm);

   fileMenu->addSeparator();
   fileMenu->addAction(tr("E&xit"), this, [this](){
      QWidget::close();
   }, tr("Ctrl+q"));

   editMenu= menuBar()->addMenu(tr("&Edit"));
   // TO DO: *** function; shortcut key(s) Ctrl + Z ***
   //editMenu->addAction(tr("&Undo"));
   editMenu->addAction(tr("Cle&ar Screen"), this, [this]() {
      view->clear_scene();
      show();
   }, tr("Shift+0"));

   circuitMenu= menuBar()->addMenu(tr("&Circuit"));
   circuitMenu->addAction(a_compile);
   circuitMenu->addAction(tr("&Read Circuit"), this, [this](){
      readCircuitDialog(graphreadcircuit);
   }, tr("Ctrl+r"));

   graphsMenu= menuBar()->addMenu(tr("&Graphs"));
   graphsMenu->addAction(a_addGate);
   graphsMenu->addAction(a_addLattice);
}

void MainWindow::exitButton() {
   settings->close();
   this->close();
}

void MainWindow::modellerMenu() {
   // 'grey out' menu items
   a_addGate->setEnabled(false);
   a_compile->setEnabled(false);
   a_openAlgorithm->setEnabled(false);
   a_saveAlgorithm->setEnabled(false);

   settings->close();   // close dialog
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

// TO DO: recut to support QAction readCircuit (Modeller.readCircuit
//    , Compiler.readCircuit)
//    + QMenu->addAction Simulator.readCircuit
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

void MainWindow::setActions() {
   a_addGate= new QAction(tr("Add Ga&te"),this);
   a_addGate->setShortcut(tr("Ctrl+t"));
//   connect(a_addGate,&QAction::triggered,[this](){gatesPalette();});   // private method

   a_addLattice= new QAction(tr("A&dd Lattice"),this);
   a_addLattice->setShortcut(tr("Ctrl+l"));
   connect(a_addLattice,&QAction::triggered,[this](){addLattice();});

   a_compile= new QAction(tr("Co&mpile"),this);
   a_compile->setShortcut(tr("Ctrl+m"));
//   connect(a_compile,&QAction::triggered,[this](){compile();});

   a_openAlgorithm= new QAction(tr("Open Al&gorithm"),this);
   a_openAlgorithm->setShortcut(tr("Ctrl+Alt+o"));
//   connect(a_openAlgorithm,&QAction::triggered,[this](){openAlgorithm();});

   a_openGraph= new QAction(tr("&Open Graph"),this);
   a_openGraph->setShortcut(tr("Ctrl+o"));
   connect(a_openGraph,&QAction::triggered
           ,[this](){ openGraphDialog(graphopenfile);});

   a_saveAlgorithm= new QAction(tr("Sa&ve Algorithm"),this);
   a_saveAlgorithm->setShortcut(tr("Ctrl+Alt+s"));
//   connect(a_saveAlgorithm,&QAction::triggered,[this](){saveAlgorithm();});

   a_saveAs= new QAction(tr("Save &As"),this);
   a_saveAs->setShortcut(tr("Ctrl+Alt+a"));
//   connect(a_saveAs,&QAction::triggered,[this](){saveAs();});

   a_saveGraph= new QAction(tr("&Save Graph"),this);
   a_saveGraph->setShortcut(tr("Ctrl+s"));
   connect(a_saveGraph,&QAction::triggered,this
           ,[this](){ saveGraphDialog(graphsavefile);});
}

void MainWindow::simulatorMenu() {
   // 'grey out' menu items
   a_addLattice->setEnabled(false);
   a_compile->setEnabled(false);
   a_openGraph->setEnabled(false);
   a_saveAs->setEnabled(false);
   a_saveGraph->setEnabled(false);

   settings->close();   // close dialog
}