#ifndef TUQ_ALGORITHMLATTICE_HPP
#define TUQ_ALGORITHMLATTICE_HPP

#include "operatorpalette.hpp"
#include "signmeasure.hpp"

#include <QGraphicsScene>

// <QGraphicsScene>
#pragma once


class AlgorithmLattice : public QGraphicsScene
{
   // encompass 21 * 21 tiles
   const QRectF latticeDims {-750,-500,4150,1580};

   unsigned int maxRow {0};
   unsigned int * maxRowMarker= & maxRow;

   unsigned int nodeRow {0};
   unsigned int * rowMarker= & nodeRow;

   QString ket0 {"0"};
   QString ketPlus {"+"};

   SignMeasure * p_endOfRow;
   SignMeasure * p_initialiseRow;
   SignMeasure * p_operatorType;

   void addRow();
   void placeOperator(QString, unsigned int);
   void prepareOperator(SignMeasure &, unsigned int, unsigned int);

public:
   explicit AlgorithmLattice(QWidget * parent= nullptr);

   unsigned int columnAtRow [21]= {0};
   OperatorPalette * p_operators;
};

#endif //TUQ_ALGORITHMLATTICE_HPP
