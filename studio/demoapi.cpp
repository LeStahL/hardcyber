#include "demoapi.h"

extern "C" {
#include "config.h"
#include "engine/renderer.h"
#include "engine/loader.h"
#include "engine/orchestrator.h"
}


DemoApi DemoApi::api;

const OpenGLSettings &DemoApi::getOpenGlSettings() const
{
    return opengl_settings;
}

void DemoApi::initializeGL()
{
    rInitializeRenderer();
    lInitializeLoader();
}

void DemoApi::resizeView(int w, int h)
{
    ::w = w;
    ::h = h;
    glViewport(0, 0, w, h);
}

void DemoApi::setTimeNow(double now)
{
    t_now = now;
}

double DemoApi::getTimeNow() const
{
    return t_now;
}

void DemoApi::setTimeStart(double start)
{
    t_start = start;
}

double DemoApi::getTimeStart() const
{
    return t_start;
}

void DemoApi::setTimeEnd(double end)
{
    t_end = end;
}

double DemoApi::getTimeEnd() const
{
    return t_end;
}

void DemoApi::renderFrame()
{
    lDrawLoadingScreen();
}
