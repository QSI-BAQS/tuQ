#ifndef TUQ_ALGORITHMLATTICE_HPP
#define TUQ_ALGORITHMLATTICE_HPP

#include "operatorpalette.hpp"
#include "signmeasure.hpp"

#include <QGraphicsScene>

// <QGraphicsScene>
#pragma once


class AlgorithmLattice : public QGraphicsScene
{
   // 21 * 21 tiles
   const QRectF latticeDims {-750,-500,4150,1580};

   // to cap adds of tiles at 21 * 21, use this?
   unsigned int columnAtRow [21]= {0};

   unsigned int maxRow {0};
   unsigned int * maxRowMarker= & maxRow;

   unsigned int nodeRow {0};
   unsigned int * rowMarker= & nodeRow;

   QString ket0 {"0"};
   QString ketPlus {"+"};
   SignMeasure * p_initialiseRow;

   OperatorPalette * p_operators;
   SignMeasure * p_operatorType;

   void addRow();
   void placeOperator(QString, unsigned int);
   void prepareOperator(SignMeasure &, unsigned int, unsigned int);

public:
   explicit AlgorithmLattice(QWidget * parent= nullptr);
};

#endif //TUQ_ALGORITHMLATTICE_HPP
