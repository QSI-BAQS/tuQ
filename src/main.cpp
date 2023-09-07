#include "gui/mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication tuq(argc, argv);
   MainWindow w;
   w.show();

   return tuq.exec();
}
