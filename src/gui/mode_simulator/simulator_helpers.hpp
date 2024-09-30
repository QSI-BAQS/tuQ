#ifndef TUQ_SIMULATOR_HELPERS_HPP
#define TUQ_SIMULATOR_HELPERS_HPP

#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>
#include <QPushButton>


class LatticeStats : public QGraphicsItem
{
   unsigned long perimeterE {};
   unsigned long perimeterS {};

   const QRectF patternRect {-22,-15,152,56};

public:
   explicit LatticeStats(unsigned long, unsigned long);

   [[nodiscard]] QRectF boundingRect() const override { return patternRect; }
   void paint(QPainter *, const QStyleOptionGraphicsItem *
         , QWidget *) override;

   const unsigned long & valPerimeterE= perimeterE;
   const unsigned long & valPerimeterS= perimeterS;

   void setPerimeterE(unsigned long east) { perimeterE= east; }
   void setPerimeterS(unsigned long south) { perimeterS= south; }
};

const static int latticeDim {21};
extern const QPointF nodeAddress [latticeDim][latticeDim];

QPushButton * h_createOperatorButton(const QString &);

#endif //TUQ_SIMULATOR_HELPERS_HPP

