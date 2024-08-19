//
// represent measurements of x/y/z designate
//

#include "signmeasure.hpp"


// public:
SignMeasure::SignMeasure(QString & sign_measure, QGraphicsItem * parent)
   : designate(sign_measure) {}

QRectF SignMeasure::boundingRect() const {
   return {-22,-15,152,56};
}

void SignMeasure::paint(QPainter * painter
      , const QStyleOptionGraphicsItem * option
      , QWidget * widget) {
   Q_UNUSED(option)
   Q_UNUSED(widget)

   if (designate == "0"){
      // row-initialising ket, framing
      QRectF backdrop {-22,-15,56,56};
      painter->setPen(QPen(Qt::black,2));
      painter->setBrush(Qt::white);
      painter->drawEllipse(backdrop);

      // row-initialising ket
      painter->setPen(QPen(Qt::blue,18));
      painter->setFont(QFont("Times New Roman",24));
      // UTF-16: vertical line; mathematical right angle bracket
      QString initialise {QChar(0x007C) % designate % QChar(0x27E9)};
      painter->drawText(backdrop, Qt::AlignCenter, initialise);
   }
   else {
      // measurement/pattern tile
      painter->setPen(QPen(Qt::black,2));
      painter->setBrush(Qt::white);

      if (designate == "CNOT")
         painter->drawRoundedRect(-22,-15,152,130,15,15);
      else
         painter->drawEllipse(boundingRect());

      // operator key
      painter->setPen(QPen(Qt::blue,18));
      painter->setFont(QFont("Times New Roman",24));
      painter->drawText(boundingRect(), Qt::AlignCenter, designate);
   }

   painter->setRenderHint(QPainter::Antialiasing);
}
