#ifndef TUQ_ALGORITHMLATTICE_HPP
#define TUQ_ALGORITHMLATTICE_HPP

#include "operatorpalette.hpp"
#include "signmeasure.hpp"

#include <QGraphicsScene>

// <QGraphicsScene>
#pragma once


class AlgorithmLattice : public QGraphicsScene
{
   unsigned long maxRow {0};
   unsigned long * maxRowMarker= & maxRow;

   unsigned long nodeRow {0};
   unsigned long * rowMarker= & nodeRow;

   SignMeasure * p_endOfRow {};
   SignMeasure * p_initialiseRow;
   SignMeasure * p_operatorType;

   void alignColumns(unsigned long, unsigned long);
   void placeOperator(QString, unsigned long);

public:
   explicit AlgorithmLattice(QWidget * parent= nullptr);

   unsigned long columnAtRow [21]= {0};
   QString ket0 {"0"};
   QString ketPlus {"+"};
   OperatorPalette * p_operators;

   void addRow();
   void prepareOperator(SignMeasure &, unsigned long, unsigned long);
};

#endif //TUQ_ALGORITHMLATTICE_HPP
