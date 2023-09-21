#ifndef TUQ_GRAPHVIEW_HPP
#define TUQ_GRAPHVIEW_HPP

#include "graphedge.hpp"
#include "graphvertex.hpp"

#include <QGraphicsView>
#include <QLabel>


class GraphView : public QGraphicsView
{
   Q_OBJECT

   QLabel * clabel {};
   bool cursorState {false};
   QString cursor_tag {};
   unsigned long edges_count {1};
   QGraphicsScene * scene;
   QGraphicsLineItem * tracer {};

   void setCursorLabel(QString *);

public:
   explicit GraphView(QWidget *parent= nullptr);

   unsigned long items_count(int);
   void openGraph(QString);
   void saveGraph(QString) const;
   void set_lattice(unsigned long, unsigned long);


protected:
   void keyPressEvent(QKeyEvent *) override;
   void mouseMoveEvent(QMouseEvent *) override;
   void mousePressEvent(QMouseEvent *) override;
   void mouseReleaseEvent(QMouseEvent *) override;

};

#endif //TUQ_GRAPHVIEW_HPP