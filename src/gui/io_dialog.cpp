//
// input via gui dialog
//

#include "io_dialog.hpp"

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QRegularExpression>


// public:
InputDialog::InputDialog(QString menu_function, QWidget * parent)
      : QDialog(parent), dialog_type(menu_function), form(new QFormLayout(this))
{
   form->addRow(new QLabel(dialog_type));

   auto * buttonBox= new QDialogButtonBox(QDialogButtonBox::Ok
                                          | QDialogButtonBox::Cancel,Qt::Horizontal, this);
   form->addRow(buttonBox);

   QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
   QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

