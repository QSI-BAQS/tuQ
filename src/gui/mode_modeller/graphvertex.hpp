#ifndef TUQ_GRAPHVERTEX_HPP
#define TUQ_GRAPHVERTEX_HPP

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPainter>

// <QPainter>
#pragma once


class GraphEdge;

class GraphVertex : public QGraphicsEllipseItem
{
   QMenu * contextmenu_v {};

   QVector<GraphEdge *> edges;

   // vertex data
   QSizeF radius {45,45};
   QPointF topleft {0,0};
   QRectF vertexboundaryrect {topleft, radius};

   // vertex rendering
   QPen vertexcircumferencepen {Qt::black, 2};
   QBrush vertexfill {QColor::fromRgb(245,245,245)};   // 'white smoke'

   // vertex ID
   class IDs {
   public:
      unsigned long vid {};
      char measure_prompt {};
   };

   // flags for painting vertex ID
   enum class id_flag {idUL, idC};
   id_flag render {id_flag::idUL};
   QFont vertexidfont {"SansSerif", 8, QFont::Normal};
   QPen vertexidpen {Qt::darkBlue, 1};

public:
   // qgraphicsitem_cast (type), QGraphicsEllipseItem::Type = 4
   explicit GraphVertex(QMenu *, unsigned long vid= 0
         , QGraphicsItem * parent= nullptr);

   IDs id;

   enum class measure_char {X, Y, Z, N};

   const QVector<GraphEdge *> * alledges {& edges};
   const unsigned long * vertexID {& id.vid};

   void add_edge(GraphEdge * edge) { edges.push_back(edge); };
   void remove_edge(GraphEdge * edge) { edges.removeAll(edge); };
   void resetVertexColour(QColor, qreal= 2, QColor= QColor(245,245,245));
   void resetVertexID(measure_char= measure_char::N);

protected:
   void contextMenuEvent(QGraphicsSceneContextMenuEvent *) override;
   QVariant itemChange(GraphicsItemChange, const QVariant &) override;
   void paint(QPainter *, const QStyleOptionGraphicsItem *
              , QWidget *) override;
};

#endif //TUQ_GRAPHVERTEX_HPP
