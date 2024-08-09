//
// represent measurements of x/y/z basis
//

#include "signmeasure.hpp"


// public:
SignMeasure::SignMeasure(QString & sign_measure, QGraphicsItem * parent)
   : basis(sign_measure) {}

QRectF SignMeasure::boundingRect() const {
   return {-22,-15,152,56};
}

void SignMeasure::paint(QPainter * painter
      , const QStyleOptionGraphicsItem * option
      , QWidget * widget) {
   Q_UNUSED(option)
   Q_UNUSED(widget)

   // measurement tile
   painter->setPen(QPen(Qt::black,2));
   painter->setBrush(Qt::white);

   if (basis == "CNOT")
      painter->drawRoundedRect(-22,-15,152,130,15,15);   // TO DO: doesn't always render completely
   else
      painter->drawEllipse(boundingRect());

   // operator key
   painter->setPen(QPen(Qt::blue,18));
   painter->setFont(QFont("Times New Roman",24));
   painter->drawText(boundingRect(),Qt::AlignCenter,basis);
   painter->setRenderHint(QPainter::Antialiasing);
}
