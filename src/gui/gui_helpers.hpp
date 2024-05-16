#ifndef TUQ_GUI_HELPERS_HPP
#define TUQ_GUI_HELPERS_HPP

#include "graphedge.hpp"
#include "graphvertex.hpp"

#include <QDialog>
#include <QFormLayout>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QRegExp>


class GraphSelect : public QDialog
{
   QGroupBox * verticalGroupBox;

   void createVerticalGroupBox();

public:
   explicit GraphSelect(QWidget * parent= nullptr);

   QPushButton * buttons[4];   // tuQ settings buttons
};

class InputDialog : public QDialog
{
   QString dialog_type;

public:
   explicit InputDialog(QString, QWidget * parent= nullptr);

   QFormLayout * form;
};


void h_deleteEdge(GraphEdge *, QGraphicsScene &);
void h_deleteVertex(GraphVertex &, QGraphicsScene &);
unsigned long h_itemCounter(int, const QGraphicsScene &);
void h_localComplementation(GraphVertex &, QGraphicsScene &, QMenu *);

#endif //TUQ_GUI_HELPERS_HPP
