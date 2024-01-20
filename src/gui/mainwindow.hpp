#ifndef TUQ_MAINWINDOW_HPP
#define TUQ_MAINWINDOW_HPP

#include "graphview.hpp"
#include "gui_helpers.hpp"

#include <QMainWindow>


class MainWindow : public QMainWindow
{
   Q_OBJECT


   QMenu * circuitMenu;
   QMenu * editMenu;
   QMenu * fileMenu;
   QMenu * latticeMenu;
   GraphView * view {};

   void createMenus();

   void addLattice();
   void openGraphDialog(const QString *);
   void readCircuitDialog(const QString *);
   void saveGraphDialog(const QString *);

public:
   explicit MainWindow(QWidget * parent= nullptr);

   const QString * graphopenfile;
   const QString * graphreadcircuit;
   const QString * graphsavefile;
};

#endif // TUQ_MAINWINDOW_HPP