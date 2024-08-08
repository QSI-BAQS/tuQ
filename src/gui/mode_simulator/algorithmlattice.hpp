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
// TO DO: array of row/column index to cap adds of tiles at 21 * 21?
   unsigned int maxRow {0};
   unsigned int nodeColumn {0};
   unsigned int nodeRow {0};
   unsigned int * columnMarker= & nodeColumn;
   unsigned int * maxRowMarker= & maxRow;
   unsigned int * rowMarker= & nodeRow;

   OperatorPalette * p_operators;
   SignMeasure * p_operatorType;

   void addRow(unsigned int);
   void placeOperator(QString, unsigned int *);

public:
   explicit AlgorithmLattice(QWidget * parent= nullptr);
};

#endif //TUQ_ALGORITHMLATTICE_HPP
