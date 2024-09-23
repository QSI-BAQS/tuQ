#ifndef TUQ_SIMULATOR_HELPERS_HPP
#define TUQ_SIMULATOR_HELPERS_HPP

#include <QPointF>
#include <QPushButton>


const static int latticeDim {21};
extern const QPointF nodeAddress [latticeDim][latticeDim];

QPushButton * h_createOperatorButton(const QString &);

#endif //TUQ_SIMULATOR_HELPERS_HPP

