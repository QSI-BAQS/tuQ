//
// specify object, 'operator palette'
//

#include "operatorpalette.hpp"

#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>


// prototype:
QPushButton * h_createOperatorButton(const QString &);

// public:
OperatorPalette::OperatorPalette(QWidget * parent) : QDialog(parent)
{
   setOperatorPalette();

   auto * dialogGrid= new QGridLayout;
   dialogGrid->addWidget(p_groupBox);

   setLayout(dialogGrid);
}

// private:
void OperatorPalette::setOperatorPalette() {
   p_groupBox= new QGroupBox(tr("simulator patterns"));
   p_groupBox->setAlignment(Qt::AlignHCenter);
   auto * p_gridLayout= new QGridLayout;

   unsigned short row {0};
   unsigned short column {0};
   for (unsigned short i= 0; i < pattern_nr; ++i) {
      pattern_buttons[i]= h_createOperatorButton(patterns[i]);

      if (i == 8)
         p_gridLayout->addWidget(pattern_buttons[8],3,1,1,1);   // 'T' pattern
      else {
         if (i > 0){
            if ((i % 3) == 0){
               row += 1;
               column= 0;
            }
            else if ((i % 3) == 1)
               column= 1;
            else
               column= 2;
         }

         p_gridLayout->addWidget(pattern_buttons[i],row,column,1,1);
      }
   }
   // the 'pattern_buttons + 1' function, 'change wire'
   pattern_buttons[9]= h_createOperatorButton("change wire");
   p_gridLayout->addWidget(pattern_buttons[9],4,0,1,3);

   p_groupBox->setLayout(p_gridLayout);
}

// helpers
QPushButton * h_createOperatorButton(const QString & operatorPattern) {
   auto * pattern= new QPushButton;

   // button text and formatting
   pattern->setStyleSheet("QPushButton { color: blue; }");
   QFont buttonFont= pattern->font();
   buttonFont.setFamily("Times New Roman");
   buttonFont.setPointSize(18);
   pattern->setFont(buttonFont);
   pattern->setText(operatorPattern);

   return pattern;
}
