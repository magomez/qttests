#include <QApplication>
#include "widget.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Widget widget(0);
    widget.show();

    return app.exec();
}
