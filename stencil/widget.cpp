#include "widget.h"

Widget::Widget()
    : QGLWidget()
{
        setFixedSize(600, 400);
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::white);
    painter.fillRect(0, 0, width(), height(), Qt::black); 
    
    painter.setFont(QFont("Arial", 30));
    painter.drawText(0, 100, "metrological");

    painter.setFont(QFont("Arial", 70));
    painter.drawText(0, 200, "metrological");

    painter.setFont(QFont("Arial", 100));
    painter.drawText(0, 350, "metrological");

    painter.end();
}
