#include <QApplication>
#include "widget.h"
#include <QGLContext>
#include <stdio.h>
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
    , m_texture(0)
{
    setFixedSize(m_size);
    resolveGLMethods();

    glGenTextures(1, &m_texture);
    if (!m_texture) {
        printf("Viewer: error creating texture\n");
        exit(0);
    }

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    imageTargetTexture2DOES(GL_TEXTURE_2D, m_eglImage);

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.setSingleShot(false);
    timer.start(1000);
}

Widget::~Widget()
{
    glDeleteTextures(1, &m_texture);
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    QRectF rect(0, 0, m_size.width(), m_size.height());
    context()->drawTexture(rect, m_texture);
}

void Widget::resolveGLMethods()
{
    createImageKHR = (PFNEGLCREATEIMAGEKHRPROC) eglGetProcAddress("eglCreateImageKHR");
    destroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC) eglGetProcAddress("eglDestroyImageKHR");
    imageTargetTexture2DOES = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");

    if (!(createImageKHR && destroyImageKHR && imageTargetTexture2DOES)) {
        printf("Viewer: error resolving gl methods\n");
        exit(0);
    }
}
