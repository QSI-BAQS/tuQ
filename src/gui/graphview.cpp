//
// statement of purpose
//
# include "graphview.hpp"


GraphView::GraphView(QWidget *parent)
   : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
   setScene(scene);

   clabel= new QLabel;
   clabel->setWindowFlag(Qt::ToolTip);
   clabel->setAttribute(Qt::WA_TranslucentBackground);
   clabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
}


void GraphView::set_lattice(unsigned long m, unsigned long n) {
//   circuit-to-graph layout
//   pre-condition:
//      - json input is well-formed,
//      - composition and layout of gates passes input checks.
//   post-condition: the count of measurement patterns, including edges,
//      strictly reconciles with the count of (input) circuit gates
   unsigned long id {1};
   qreal xinc {75};
   qreal yinc {75};

   for (int i= 0; i < m; ++i) {
      for (int j= 0; j < n; ++j) {
         auto vertex= new GraphVertex(id);
         vertex->setPos(j*xinc,i*yinc);
         scene->addItem(vertex);

         id += 1;
      }
   }
}

