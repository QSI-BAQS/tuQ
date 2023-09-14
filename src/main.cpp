#include "gui/graphview.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication tuq(argc, argv);

   // move and reformat as helper function: begin
   auto * view= new GraphView();
   view->setWindowTitle("tuQ");
   view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
   // helper function: end

//   view->set_lattice(15,15);
   view->show();

   return tuq.exec();
}
