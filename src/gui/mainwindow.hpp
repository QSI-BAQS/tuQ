#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "graphview.hpp"

#include <QMainWindow>


class MainWindow : public QMainWindow
{
   Q_OBJECT

   GraphView * view {};

public:
   explicit MainWindow(QWidget * parent= nullptr);

};

#endif // MAINWINDOW_HPP