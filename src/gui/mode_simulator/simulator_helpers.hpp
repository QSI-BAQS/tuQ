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

   const QRectF patternRect {-22,-15,152,52};

public:
   explicit LatticeStats(unsigned long, unsigned long);

   unsigned long countTPatterns {};

   [[nodiscard]] QRectF boundingRect() const override { return patternRect; }
   void paint(QPainter *, const QStyleOptionGraphicsItem *
         , QWidget *) override;
   unsigned long * p_perimeterE= &perimeterE;
   unsigned long * p_perimeterS= &perimeterS;
};

const static int latticeDim {21};
extern const QPointF nodeAddress [latticeDim][latticeDim];
const static QPointF statsPos {-725, -550};

QPushButton * h_createOperatorButton(const QString &);

#endif //TUQ_SIMULATOR_HELPERS_HPP

