#include <QApplication>
#include "renderer.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Renderer renderer;

    return app.exec();
}
