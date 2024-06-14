#ifndef TUQ_COMPILERVIEW_HPP
#define TUQ_COMPILERVIEW_HPP

#include <fstream>
#include <QGraphicsView>


class CompilerView : public QGraphicsView
{
   Q_OBJECT

   QGraphicsScene * c_scene;

public:
   explicit CompilerView(QWidget * parent= nullptr);

   void clear_scene() { c_scene->clear(); }
//   void readCircuit(const QString &);
};

#endif //TUQ_COMPILERVIEW_HPP
