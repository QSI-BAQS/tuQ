#ifndef GRAPHVIEW_HPP
#define GRAPHVIEW_HPP

#include "graphedge.hpp"
#include "graphvertex.hpp"

#include <QGraphicsView>
#include <QLabel>


class QGraphicsLineItem;

class GraphView : public QGraphicsView
{
   Q_OBJECT

   QLabel * clabel {};
   bool cursorState {false};
   unsigned long edges_count {1};
   QGraphicsScene * scene;
   QString cursor_tag {};
   QGraphicsLineItem * tracer {};
   unsigned long vertices_count {1};

   void setCursorLabel(QString *);

public:
   explicit GraphView(QWidget *parent= nullptr);

   void set_lattice(unsigned long, unsigned long);

protected:
   void keyPressEvent(QKeyEvent *) override;
   void mouseMoveEvent(QMouseEvent *) override;
   void mousePressEvent(QMouseEvent *) override;
   void mouseReleaseEvent(QMouseEvent *) override;

};

#endif //GRAPHVIEW_HPP