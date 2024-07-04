//
// specify object, 'operator palette'
//

#include "operatorpalette.hpp"

#include <QGridLayout>
#include <QSpacerItem>

// prototype:
QPushButton * h_createOperatorButton(const QString &);

// public:
OperatorPalette::OperatorPalette(QWidget * parent) : QDialog(parent)
{
   createMeasurementsGroupBox();
   createPatternsGroupBox();

   auto * dialogLayout= new QVBoxLayout;
   auto * dialogSpacer= new QSpacerItem(1,15);

   dialogLayout->addWidget(p_measurements_groupBox);
   dialogLayout->addSpacerItem(dialogSpacer);
   dialogLayout->addWidget(p_patterns_groupBox);

   // add changeRow to OperatorPalette
   dialogLayout->addSpacerItem(dialogSpacer);
   auto * p_changerowGridLayout= new QGridLayout;
   changeRow= h_createOperatorButton("change row");
   p_changerowGridLayout->addWidget(changeRow, 0, 0, 1, 3);
   dialogLayout->addWidget(changeRow);

   setLayout(dialogLayout);
}

// private:
void OperatorPalette::createMeasurementsGroupBox() {
   p_measurements_groupBox= new QGroupBox(tr("measurement bases"));
   p_measurements_groupBox->setAlignment(Qt::AlignCenter);

   auto * p_hboxLayout= new QHBoxLayout;

   measurement_buttons= new QButtonGroup;
   for (int i= 0; i < measurements_nr; ++i) {
      QPushButton * measurement_button= h_createOperatorButton(measurements[i]);
      measurement_buttons->addButton(measurement_button,i);

      p_hboxLayout->addWidget(measurement_button);
   }
   p_measurements_groupBox->setLayout(p_hboxLayout);
}

void OperatorPalette::createPatternsGroupBox() {
   p_patterns_groupBox= new QGroupBox(tr("measurement patterns"));
   p_patterns_groupBox->setAlignment(Qt::AlignHCenter);

   auto * p_patternsGridLayout= new QGridLayout;

   pattern_buttons= new QButtonGroup;
   // add patterns to p_patternsGridLayout; group as pattern_buttons
   unsigned short row {0};
   unsigned short column {0};
   for (unsigned short i= 0; i < pattern_nr; ++i) {
      QPushButton * pattern_button= h_createOperatorButton(patterns[i]);
      pattern_buttons->addButton(pattern_button,i);

      if (i == 7)
         // 'T' pattern
         p_patternsGridLayout->addWidget(pattern_button, 2, 2, 1, 1);
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

         p_patternsGridLayout->addWidget(pattern_button, row, column, 1, 1);
      }
   }
   p_patterns_groupBox->setLayout(p_patternsGridLayout);
}

// helpers
QPushButton * h_createOperatorButton(const QString & marker) {
   auto * clusterOperator= new QPushButton;
   // button text and formatting
   clusterOperator->setStyleSheet("QPushButton { color: blue; }");

   QFont buttonFont= clusterOperator->font();
   buttonFont.setFamily("Times New Roman");
   buttonFont.setPointSize(18);

   clusterOperator->setFont(buttonFont);
   clusterOperator->setText(marker);

   return clusterOperator;
}
