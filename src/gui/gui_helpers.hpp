#ifndef TUQ_GUI_HELPERS_HPP
#define TUQ_GUI_HELPERS_HPP

#include <QDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>


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

#endif //TUQ_GUI_HELPERS_HPP
