#ifndef TUQ_ALGORITHMLATTICE_HPP
#define TUQ_ALGORITHMLATTICE_HPP

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

   // 21 * 21 tiles
   const QRectF latticeDims {-750,-500,4150,1580};

   // to cap adds of tiles at 21 * 21, use this?
   unsigned int columnAtRow [21]= {0};

   unsigned int maxRow {0};
   unsigned int * maxRowMarker= & maxRow;

   unsigned int nodeRow {0};
   unsigned int * rowMarker= & nodeRow;

   OperatorPalette * p_operators;
   SignMeasure * p_operatorType;

   void placeOperator(QString, unsigned int);

private slots:
   void addRow();

public:
   explicit AlgorithmLattice(QWidget * parent= nullptr);
};

#endif //TUQ_ALGORITHMLATTICE_HPP
