#include "counterwidget.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try {
        CounterWidget w;
        w.show();
        return a.exec();
    }
    catch (const char* msg) {
        qDebug() << msg;
        a.quit();
    }
}
