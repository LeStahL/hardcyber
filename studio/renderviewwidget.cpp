#include "renderviewwidget.h"
#include "demoapi.h"

#include <QOpenGLContext>


RenderViewWidget::RenderViewWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    setup();
}

void RenderViewWidget::initializeGL()
{
    DemoApi::api.initializeGL();
}

void RenderViewWidget::resizeGL(int w, int h)
{
    DemoApi::api.resizeView(w, h);
}

void RenderViewWidget::paintGL()
{
    DemoApi::api.renderFrame();
}

void RenderViewWidget::setup()
{
    QSurfaceFormat surfaceFormat;

    { // Translate OpenGlSettings to QSurfaceFormat
        OpenGLSettings openGlSettings = DemoApi::api.getOpenGlSettings();

        // Basic settings
        surfaceFormat.setRenderableType(QSurfaceFormat::RenderableType::OpenGL);
        surfaceFormat.setVersion(openGlSettings.majorVersion, openGlSettings.minorVersion);
        surfaceFormat.setSamples(openGlSettings.samples);

        // Channel widths
        surfaceFormat.setRedBufferSize(openGlSettings.redBits);
        surfaceFormat.setGreenBufferSize(openGlSettings.greenBits);
        surfaceFormat.setBlueBufferSize(openGlSettings.blueBits);
        surfaceFormat.setAlphaBufferSize(openGlSettings.alphaBits);
        surfaceFormat.setDepthBufferSize(openGlSettings.depthBits);
        surfaceFormat.setStencilBufferSize(openGlSettings.stencilBits);

        switch (openGlSettings.profile)
        {
        case OpenGLProfile::CoreProfile:
            surfaceFormat.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);
            break;

        case OpenGLProfile::CompatibilityProfile:
            surfaceFormat.setProfile(QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile);
            break;
        }

        if (openGlSettings.useSRGB == 0)
        {
            surfaceFormat.setColorSpace(QSurfaceFormat::ColorSpace::DefaultColorSpace);
        }
        else
        {
            surfaceFormat.setColorSpace(QSurfaceFormat::ColorSpace::sRGBColorSpace);
        }

        switch (openGlSettings.swapChain)
        {
        case SwapChain::DoubleBuffer:
            surfaceFormat.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
            break;

        case SwapChain::TripleBuffer:
            surfaceFormat.setSwapBehavior(QSurfaceFormat::SwapBehavior::TripleBuffer);
            break;
        }
    }

    setFormat(surfaceFormat);
}
