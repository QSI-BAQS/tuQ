#ifndef TUQ_OPERATORPALETTE_HPP
#define TUQ_OPERATORPALETTE_HPP

#include <QButtonGroup>
#include <QDialog>
#include <QGroupBox>
#include <QPushButton>
#include <QStringBuilder>


class OperatorPalette : public QDialog
{
   const static unsigned short measurements_nr {3};
   const static unsigned short pattern_nr {8};

   QGroupBox * p_measurements_groupBox= nullptr;
   QGroupBox * p_patterns_groupBox= nullptr;

   void createMeasurementsGroupBox();
   void createPatternsGroupBox();

public:
   explicit OperatorPalette(QWidget * parent= nullptr);

   const QChar sigma {0x03C3};   // UTF-16: lower-case sigma
   const QString measurements[measurements_nr] {sigma % " x",sigma % " y",sigma % " z"};

   const QString patterns[pattern_nr] {"X-rotation","Y-rotation","Z-rotation"
                                       ,"Hadamard","S","CNOT","Swap","T"};

   QButtonGroup * measurement_buttons;
   QButtonGroup * pattern_buttons;
   QPushButton * changeRow;
};

#endif //TUQ_OPERATORPALETTE_HPP
