#ifndef TUQ_SIGNMEASURE_HPP
#define TUQ_SIGNMEASURE_HPP

#include <QGraphicsItem>
#include <QPainter>
#include <QStringBuilder>

// <QGraphicsItem>, <QStringBuilder>
#pragma once


class SignMeasure : public QGraphicsItem
{
   QString designate {};

   const QPen designatePen {Qt::blue, 18};
   const QRectF patternRect {-22,-15,152,56};

public:
   explicit SignMeasure(QString &);

   // SignMeasure::Type = 65537
   enum { Type= UserType + 1 };

   // proxy for CZ gate on adjacent operators
   SignMeasure * p_CZ= nullptr;

   QRectF boundingRect() const override { return patternRect; };
   QString showOperator() { return designate; };
   void paint(QPainter *, const QStyleOptionGraphicsItem *
              , QWidget *) override;
   int type() const override { return Type; };
};

#endif //TUQ_SIGNMEASURE_HPP
