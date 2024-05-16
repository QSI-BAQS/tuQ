#ifndef TUQ_MAINWINDOW_HPP
#define TUQ_MAINWINDOW_HPP

#include "graphview.hpp"
#include "gui_helpers.hpp"

#include <QMainWindow>


class MainWindow : public QMainWindow
{
   Q_OBJECT

   GraphSelect * settings;
   GraphView * view {};

   QAction * a_addGate;
   QAction * a_addLattice;
   QAction * a_compile;
   QAction * a_openAlgorithm;
   QAction * a_openGraph;
   QAction * a_readCircuit;
   QAction * a_saveAlgorithm;
   QAction * a_saveGraph;
   QAction * a_simulate;

   QMenu * circuitMenu;
   QMenu * editMenu;
   QMenu * fileMenu;
   QMenu * graphMenu;

   void createMenus();
   void setActions();

   void addLattice();
//   void gatesPalette();
   void dialogOpen(const QString *);
   void readCircuitDialog(const QString *);
   void dialogSave(const QString *);

private slots:
   void compilerMenu();
   void exitButton();
   void modellerMenu();
   void simulatorMenu();

public:
   explicit MainWindow(QWidget * parent= nullptr);

   const QString * algorithmopenfile;
   const QString * algorithmsavefile;
   const QString * graphopenfile;
   const QString * graphreadcircuit;
   const QString * graphsavefile;
};

#endif // TUQ_MAINWINDOW_HPP