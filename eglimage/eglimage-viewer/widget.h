#include <QGLWidget>
#include <QTimer>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>

class Widget : public QGLWidget
{
    Q_OBJECT
public:
    Widget(EGLImageKHR eglImage);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void resolveGLMethods();

    QSize m_size;
    QTimer timer;
    EGLImageKHR m_eglImage;
};
