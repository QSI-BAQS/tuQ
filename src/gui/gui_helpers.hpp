#ifndef TUQ_GUI_HELPERS_HPP
#define TUQ_GUI_HELPERS_HPP

#include <QDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>

// <QDialog>, <QGroupBox>, <QPushButton>
#pragma once


class GraphSelect : public QDialog
{
   QGroupBox * verticalGroupBox= nullptr;

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
