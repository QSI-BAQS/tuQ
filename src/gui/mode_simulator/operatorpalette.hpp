#ifndef TUQ_OPERATORPALETTE_HPP
#define TUQ_OPERATORPALETTE_HPP

#include <QDialog>
#include <QGroupBox>


class OperatorPalette : public QDialog
{
   QGroupBox * p_groupBox= nullptr;

   const static unsigned short pattern_nr {9};
   // 0x2020: dagger
   QString patterns [pattern_nr] {"X","Y","Z","Hadamard","S",QChar(0x2020)
         ,"CNOT","Swap","T"};

   void setOperatorPalette();

public:
   explicit OperatorPalette(QWidget * parent= nullptr);

   QPushButton * pattern_buttons[pattern_nr + 1];
};


#endif //TUQ_OPERATORPALETTE_HPP
