#include <QtWidgets/QApplication>
#include "MyView.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyView view;
    view.show();
    return a.exec();
}
