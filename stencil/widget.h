#include <QGLWidget>

class Widget : public QGLWidget
{
    Q_OBJECT
public:
    Widget();

protected:
    void paintEvent(QPaintEvent *event);
};
