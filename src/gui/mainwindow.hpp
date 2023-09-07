#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#pragma once

#include "graphview.hpp"

#include <QMainWindow>


class MainWindow : public QMainWindow
{
   Q_OBJECT

// 'class members are private by default'
   GraphView * view {};
   QGraphicsView * view2 {};


public:
   explicit MainWindow(QWidget * parent= nullptr);


};

#endif // MAINWINDOW_HPP