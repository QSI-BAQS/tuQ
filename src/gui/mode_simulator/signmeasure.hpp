#ifndef TUQ_SIGNMEASURE_HPP
#define TUQ_SIGNMEASURE_HPP

#include <QGraphicsSimpleTextItem>
#include <QPainter>


class SignMeasure : public QGraphicsSimpleTextItem
{
   QString basis {};

public:
   // QGraphicsSimpleTextItem::Type = 9
   explicit SignMeasure(QString &, QGraphicsItem * parent= nullptr);

   QRectF boundingRect() const override;
   void paint(QPainter *, const QStyleOptionGraphicsItem *
              , QWidget *) override;
};

#endif //TUQ_SIGNMEASURE_HPP
