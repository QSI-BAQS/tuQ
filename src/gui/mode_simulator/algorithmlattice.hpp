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

   unsigned long columnAtRow [latticeDim]= {0};
   QString ket0 {0x03C8};   // 'Greek small letter psi'
   QString ketPlus {"+"};
   OperatorPalette * p_operators;
   LatticeStats * p_stats;

   void addRow();
   void prepareOperator(SignMeasure &, unsigned long, unsigned long);
};

#endif //TUQ_ALGORITHMLATTICE_HPP
