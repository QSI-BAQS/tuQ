#ifndef TUQ_SIMULATORSCENE_HPP
#define TUQ_SIMULATORSCENE_HPP

#include "operatorpalette.hpp"

#include <QGraphicsScene>

#pragma once


class AlgorithmLattice : public QGraphicsScene
{
   // 'The Q_OBJECT macro must appear in the private section of a class
   // definition that declares its own signals and slots...'
   Q_OBJECT

   OperatorPalette * p_operators;

public:
   explicit AlgorithmLattice(QWidget * parent= nullptr);
};

#endif //TUQ_SIMULATORSCENE_HPP
