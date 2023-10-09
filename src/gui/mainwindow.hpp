#ifndef TUQ_MAINWINDOW_HPP
#define TUQ_MAINWINDOW_HPP

#include "graphview.hpp"

#include <QMainWindow>


class MainWindow : public QMainWindow
{
   Q_OBJECT

   QMenu * fileMenu;
   GraphView * view {};

   void createMenus();
   void openGraphDialog(const QString *);
   void saveGraphDialog(const QString *);

public:
   explicit MainWindow(QWidget * parent= nullptr);

   const QString * graphopenfile;
   const QString * graphsavefile;
};

#endif // TUQ_MAINWINDOW_HPP