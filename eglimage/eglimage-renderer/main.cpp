#include <QApplication>
#include <QProcess>
#include "renderer.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Renderer renderer;

    QProcess process;
    QString program = "/usr/bin/eglimage-viewer";
    QStringList parameters;
    process.setProcessChannelMode(QProcess::ForwardedChannels);
    parameters << QString::number(renderer.eglImage());
    process.start(program, parameters);

    return app.exec();
}
