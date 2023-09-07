#ifndef GRAPHVIEW_HPP
#define GRAPHVIEW_HPP
#pragma once

#include "graphvertex.hpp"

#include <QGraphicsView>
#include <QLabel>


class GraphView : public QGraphicsView
{
   Q_OBJECT

// 'class members are private by default'
   QLabel * clabel {};
   QGraphicsScene * scene;


// 'keep interfaces minimal'
public:
   explicit GraphView(QWidget *parent= nullptr);

   void set_lattice(unsigned long, unsigned long);


// 'keep interfaces minimal'
protected:


};

#endif //GRAPHVIEW_HPP