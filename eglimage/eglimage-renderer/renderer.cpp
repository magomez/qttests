#include <QApplication>
#include "renderer.h"
#include <QOpenGLContext>
#include <stdio.h>
#include <QSize>
#include <QOpenGLFramebufferObject>
#include <QOpenGLPaintDevice>
#include <QOpenGLContext>
#include <QTime>
#include <QDesktopWidget>
#include <QPainter>

static PFNEGLCREATEIMAGEKHRPROC createImageKHR = 0;
static PFNEGLDESTROYIMAGEKHRPROC destroyImageKHR = 0;
static PFNGLEGLIMAGETARGETTEXTURE2DOESPROC imageTargetTexture2DOES = 0;

Renderer::Renderer()
    : QObject()
    , m_size(QApplication::desktop()->screenGeometry().size())
    , m_eglImage(EGL_NO_IMAGE_KHR)
    , m_surface(0)
    , m_context(0)
    , m_fbo(0)
{
    resolveGLMethods();

    m_surface = new QOffscreenSurface;
    m_surface->create();
    m_context = new QOpenGLContext;
    m_context->create();
    m_context->makeCurrent(m_surface);

    m_fbo = new QOpenGLFramebufferObject(m_size, QOpenGLFramebufferObject::CombinedDepthStencil, GL_TEXTURE_2D, GL_RGBA);
    m_eglImage = createImageKHR(eglGetCurrentDisplay(), eglGetCurrentContext(), EGL_GL_TEXTURE_2D_KHR, (EGLClientBuffer)m_fbo->texture(), NULL);
    if (m_eglImage == EGL_NO_IMAGE_KHR) {
        printf("Error creating EGLimage\n");
        exit(0);
    } else {
        printf("Created EGLImage %d\n", (uint32_t)m_eglImage);
    }

    connect(&timer, SIGNAL(timeout()), this, SLOT(render()));
    timer.setSingleShot(false);
    timer.start(1000);
}

Renderer::~Renderer()
{
    destroyImageKHR(eglGetCurrentDisplay(), m_eglImage);
    delete m_fbo;
    delete m_context;
    m_surface->destroy();
    delete m_surface;
}

void Renderer::render()
{
    QString time = QTime::currentTime().toString();
    printf("Renderer: %s\n", time.toUtf8().constData());
    m_context->makeCurrent(m_surface);
    m_fbo->bind();
    QOpenGLPaintDevice *pdev = new QOpenGLPaintDevice(m_size);
    QPainter *painter = new QPainter(pdev);
    painter->setPen(Qt::white);
    painter->fillRect(0, 0, m_size.width(), m_size.height(), Qt::black); 
    painter->setFont(QFont("Arial", 100));
    painter->drawText(400, 400, time);
    painter->end();
    delete painter;
    delete pdev;
}

void Renderer::resolveGLMethods()
{
    createImageKHR = (PFNEGLCREATEIMAGEKHRPROC) eglGetProcAddress("eglCreateImageKHR");
    destroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC) eglGetProcAddress("eglDestroyImageKHR");
    imageTargetTexture2DOES = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");

    if (!(createImageKHR && destroyImageKHR && imageTargetTexture2DOES)) {
        printf("Error resolving gl methods\n");
        exit(0);
    }
}

uint32_t Renderer::eglImage()
{
    return *((uint32_t*)&m_eglImage);
}
