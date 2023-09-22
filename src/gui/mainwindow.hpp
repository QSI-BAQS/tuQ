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

public:
   explicit MainWindow(QWidget * parent= nullptr);

//   void openGraphDialog();
   void saveGraphDialog();
};

#endif // TUQ_MAINWINDOW_HPP