#include <QTimer>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <QOpenGLFramebufferObject>
#include <QOpenGLPaintDevice>
#include <QOpenGLContext>
#include <QOffscreenSurface>

class Renderer : public QObject
{
    Q_OBJECT

public:
    Renderer();
    ~Renderer();

private Q_SLOTS:
    void render();

private:
    void resolveGLMethods();

    QSize m_size;
    QTimer timer;
    EGLImageKHR m_eglImage;
    QOffscreenSurface *m_surface;
    QOpenGLContext *m_context;
    QOpenGLFramebufferObject *m_fbo;
};
