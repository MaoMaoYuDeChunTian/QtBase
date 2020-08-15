#include "ServerWidget.h"
#include "clientwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget w;
    w.show();
    ClientWidget c;
    c.move(200,200);
    c.show();

    return a.exec();
}
