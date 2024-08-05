#ifndef TUQ_ALGORITHMLATTICE_HPP
#define TUQ_ALGORITHMLATTICE_HPP

#include "operatorpalette.hpp"
#include "signmeasure.hpp"

#include <QGraphicsScene>

// <QGraphicsScene>
#pragma once


class AlgorithmLattice : public QGraphicsScene
{
   // 16 * 16 tiles
   const QRectF latticeDims {-750,-500,2850,1000};

   // {x,y}
   QPointF nodeAddress [16][16] {
         { {-725,-475}, {-548,-475}, {-371,-475}, {-194,-475}, {-17,-475}, {160,-475}, {337,-475}, {514,-475}, {691,-475}, {868,-475}, {1045,-475}, {1222,-475}, {1399,-475}, {1576,-475}, {1753,-475}, {1930,-475} },
         { {-725,-400}, {-548,-400}, {-371,-400}, {-194,-400}, {-17,-400}, {160,-400}, {337,-400}, {514,-400}, {691,-400}, {868,-400}, {1045,-400}, {1222,-400}, {1399,-400}, {1576,-400}, {1753,-400}, {1930,-400} },
         { {-725,-325}, {-548,-325}, {-371,-325}, {-194,-325}, {-17,-325}, {160,-325}, {337,-325}, {514,-325}, {691,-325}, {868,-325}, {1045,-325}, {1222,-325}, {1399,-325}, {1576,-325}, {1753,-325}, {1930,-325} },
         { {-725,-250}, {-548,-250}, {-371,-250}, {-194,-250}, {-17,-250}, {160,-250}, {337,-250}, {514,-250}, {691,-250}, {868,-250}, {1045,-250}, {1222,-250}, {1399,-250}, {1576,-250}, {1753,-250}, {1930,-250} },
         { {-725,-175}, {-548,-175}, {-371,-175}, {-194,-175}, {-17,-175}, {160,-175}, {337,-175}, {514,-175}, {691,-175}, {868,-175}, {1045,-175}, {1222,-175}, {1399,-175}, {1576,-175}, {1753,-175}, {1930,-175} },
         { {-725,-100}, {-548,-100}, {-371,-100}, {-194,-100}, {-17,-100}, {160,-100}, {337,-100}, {514,-100}, {691,-100}, {868,-100}, {1045,-100}, {1222,-100}, {1399,-100}, {1576,-100}, {1753,-100}, {1930,-100} },
         { {-725,-25}, {-548,-25}, {-371,-25}, {-194,-25}, {-17,-25}, {160,-25}, {337,-25}, {514,-25}, {691,-25}, {868,-25}, {1045,-25}, {1222,-25}, {1399,-25}, {1576,-25}, {1753,-25}, {1930,-25} },
         { {-725,50}, {-548,50}, {-371,50}, {-194,50}, {-17,50}, {160,50}, {337,50}, {514,50}, {691,50}, {868,50}, {1045,50}, {1222,50}, {1399,50}, {1576,50}, {1753,50}, {1930,50} },
         { {-725,125}, {-548,125}, {-371,125}, {-194,125}, {-17,125}, {160,125}, {337,125}, {514,125}, {691,125}, {868,125}, {1045,125}, {1222,125}, {1399,125}, {1576,125}, {1753,125}, {1930,125} },
         { {-725,200}, {-548,200}, {-371,200}, {-194,200}, {-17,200}, {160,200}, {337,200}, {514,200}, {691,200}, {868,200}, {1045,200}, {1222,200}, {1399,200}, {1576,200}, {1753,200}, {1930,200} },
         { {-725,275}, {-548,275}, {-371,275}, {-194,275}, {-17,275}, {160,275}, {337,275}, {514,275}, {691,275}, {868,275}, {1045,275}, {1222,275}, {1399,275}, {1576,275}, {1753,275}, {1930,275} },
         { {-725,350}, {-548,350}, {-371,350}, {-194,350}, {-17,350}, {160,350}, {337,350}, {514,350}, {691,350}, {868,350}, {1045,350}, {1222,350}, {1399,350}, {1576,350}, {1753,350}, {1930,350} },
         { {-725,425}, {-548,425}, {-371,425}, {-194,425}, {-17,425}, {160,425}, {337,425}, {514,425}, {691,425}, {868,425}, {1045,425}, {1222,425}, {1399,425}, {1576,425}, {1753,425}, {1930,425} },
         { {-725,500}, {-548,500}, {-371,500}, {-194,500}, {-17,500}, {160,500}, {337,500}, {514,500}, {691,500}, {868,500}, {1045,500}, {1222,500}, {1399,500}, {1576,500}, {1753,500}, {1930,500} },
         { {-725,575}, {-548,575}, {-371,575}, {-194,575}, {-17,575}, {160,575}, {337,575}, {514,575}, {691,575}, {868,575}, {1045,575}, {1222,575}, {1399,575}, {1576,575}, {1753,575}, {1930,575} },
         { {-725,650}, {-548,650}, {-371,650}, {-194,650}, {-17,650}, {160,650}, {337,650}, {514,650}, {691,650}, {868,650}, {1045,650}, {1222,650}, {1399,650}, {1576,650}, {1753,650}, {1930,650} }
   };
   unsigned int nodeColumn {0};
   unsigned int nodeRow {0};
   unsigned int * columnMarker= & nodeColumn;
   unsigned int * rowMarker= & nodeRow;

   OperatorPalette * p_operators;
   SignMeasure * p_operatorType;

   void changeRow(unsigned int *);
   void placeOperator(QString, unsigned int *);

public:
   explicit AlgorithmLattice(QWidget * parent= nullptr);
};

#endif //TUQ_ALGORITHMLATTICE_HPP
