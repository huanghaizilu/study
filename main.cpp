#include "widget.h"
#include <QApplication>
#include "connection.h"
#include "qfile.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        if (!createConnection()) return 1;
        Widget w;
        w.show();

        QFile styleFile(":/ui.qss");
        styleFile.open(QIODevice::ReadOnly);
        QString setStyleSheet(styleFile.readAll());
        a.setStyleSheet(setStyleSheet);

    return a.exec();
}
