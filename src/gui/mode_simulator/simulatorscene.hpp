#ifndef TUQ_SIMULATORSCENE_HPP
#define TUQ_SIMULATORSCENE_HPP

#include "operatorpalette.hpp"
#include "signmeasure.hpp"

#include <QGraphicsScene>

// <QGraphicsScene>
#pragma once


class AlgorithmLattice : public QGraphicsScene
{
   // 'The Q_OBJECT macro must appear in the private section of a class
   // definition that declares its own signals and slots...'
   Q_OBJECT

   OperatorPalette * p_operators;
   QGraphicsSimpleTextItem * p_operatorType;

   void placeOperator(QString);

private slots:
   void changeRow();
   void measurementsID(int);
   void patternsID(int);

public:
   explicit AlgorithmLattice(QWidget * parent= nullptr);
};

#endif //TUQ_SIMULATORSCENE_HPP
