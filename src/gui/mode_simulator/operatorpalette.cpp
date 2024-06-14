//
// specify an operators palette object
//

#include "operator_palette.hpp"

#include <QCursor>


OperatorPalette::OperatorPalette()
{
//   setToolTip();
   setCursor(Qt::OpenHandCursor);
   setAcceptedMouseButtons(Qt::LeftButton);
}
