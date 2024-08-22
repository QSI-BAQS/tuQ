#ifndef TUQ_OPERATORPALETTE_HPP
#define TUQ_OPERATORPALETTE_HPP

#include "simulator_helpers.hpp"

#include <QButtonGroup>
#include <QComboBox>
#include <QDialog>
#include <QGroupBox>
#include <QStringBuilder>


class OperatorPalette : public QDialog
{
   const static unsigned short measurements_nr {3};
   const static unsigned short pattern_nr {8};

   QGroupBox * p_measurements_groupBox= nullptr;
   QGroupBox * p_patterns_groupBox= nullptr;
   QGroupBox * p_rows_groupBox= nullptr;

   void createMeasurementsGroupBox();
   void createPatternsGroupBox();
   void createRowsGroupBox();

public:
   explicit OperatorPalette(QWidget * parent= nullptr);

   // UTF-16 hexes
   const QChar downArrow {0x2193};   // 'downwards arrow'
   const QChar slSigma {0x03C3};   // 'Greek small letter slSigma'
   const QChar upArrow {0x2191};   // 'upwards arrow'

   const QString measurements[measurements_nr] {slSigma % " x", slSigma % " y"
                                                , slSigma % " z"};

   const QString patterns[pattern_nr] {"X-rotation","Y-rotation","Z-rotation"
                                       ,"Hadamard","S", "T", "CNOT t" % upArrow
                                       , "CNOT t" % downArrow};

   QButtonGroup * measurement_buttons;
   QButtonGroup * pattern_buttons;
   QPushButton * p_addRow;
   QComboBox * possibleRows;
};

#endif //TUQ_OPERATORPALETTE_HPP
