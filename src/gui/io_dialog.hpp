#ifndef TUQ_IO_DIALOG_HPP
#define TUQ_IO_DIALOG_HPP

#include <QDialog>
#include <QFormLayout>



class InputDialog : public QDialog
{
   QString dialog_type;

public:
   explicit InputDialog(QString, QWidget * parent= nullptr);

   QFormLayout * form;

};



#endif //TUQ_IO_DIALOG_HPP
