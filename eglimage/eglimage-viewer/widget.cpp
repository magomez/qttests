#include <QApplication>
#include "widget.h"
#include <QGLContext>
#include <stdio.h>
#include <private/qopenglpaintengine_p.h>
#include <QSize>
#include <QRectF>
#include <QOpenGLFramebufferObject>
#include <QOpenGLPaintDevice>
#include <QDesktopWidget>

static PFNEGLCREATEIMAGEKHRPROC createImageKHR = 0;
static PFNEGLDESTROYIMAGEKHRPROC destroyImageKHR = 0;
static PFNGLEGLIMAGETARGETTEXTURE2DOESPROC imageTargetTexture2DOES = 0;

Widget::Widget(uint32_t eglImage)
    : QGLWidget()
    , m_size(QApplication::desktop()->screenGeometry().size())
    , m_eglImage((EGLImageKHR)eglImage)
{
    setFixedSize(m_size);
    resolveGLMethods();

    printf("                                                                          Using EGLImage %d\n", (uint32_t)m_eglImage);

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.setSingleShot(false);
    timer.start(1000);
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    printf("                                                                          Viewer redraw\n");
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    swapBuffers();
}

void Widget::resolveGLMethods()
{
    createImageKHR = (PFNEGLCREATEIMAGEKHRPROC) eglGetProcAddress("eglCreateImageKHR");
    destroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC) eglGetProcAddress("eglDestroyImageKHR");
    imageTargetTexture2DOES = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");

    if (!(createImageKHR && destroyImageKHR && imageTargetTexture2DOES)) {
        printf("Error resolving gl methods\n");
        exit(0);
    }
}
