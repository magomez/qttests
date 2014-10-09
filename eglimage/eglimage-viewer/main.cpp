#include <QApplication>
#include "widget.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Widget widget(app.arguments().at(1).toUInt());
    widget.show();

    return app.exec();
}
