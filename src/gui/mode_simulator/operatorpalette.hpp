#ifndef TUQ_OPERATOR_PALETTE_HPP
#define TUQ_OPERATOR_PALETTE_HPP

#include <QGraphicsItem>
#include <QPainter>


class OperatorPalette : public QGraphicsItem
{
public:
   // QGraphicsItem::Type = 4
   OperatorPalette();

   QRectF boundingRect() const override;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif //TUQ_OPERATOR_PALETTE_HPP
