#include "clientwidget.h"
#include "serverwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientWidget w;
    w.show();

    ServerWidget s;
    s.move(200,0);
    s.show();

    return a.exec();
}
