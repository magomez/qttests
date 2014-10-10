#include "widget.h"
#include <QDesktopWidget>
#include <QApplication>

Widget::Widget()
    : QGLWidget()
{
    setFixedSize((QApplication::desktop()->screenGeometry().size()));
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::white);
    painter.fillRect(0, 0, width(), height(), Qt::black); 
    
    painter.setFont(QFont("Arial", 30));
    painter.drawText(0, 100, "this is 30px and fine");

    painter.setFont(QFont("Arial", 70));
    painter.drawText(0, 200, "this is 70px and noisy");

    painter.setFont(QFont("Arial", 100));
    painter.drawText(0, 400, "this is 100px and noisy");

    painter.end();
}
