#ifndef LOADER_H
#define LOADER_H

#include "renderer.h"
#include "shader.h"

// Generated resources
#include "shaders.gen.h"


static float progress = 0.f;

static void lInitializeLoader()
{
    // Load loading bar shader
    sCompileShaderProgram(&shader_program_gfx_load, shader_symbols);
}

static unsigned int lNumberOfSymbols = ARRAYSIZE(shader_symbols);

static void lDrawLoadingScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program_gfx_load.handle);
    glUniform2f(shader_uniform_gfx_load_iResolution, w, h);
    glUniform1f(shader_uniform_gfx_load_iProgress, progress);

    quad();
}

// TODO(ca) Rename function to match naming scheme
static void updateBar()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Render first pass
    glViewport(0,0,w,h);

    lDrawLoadingScreen();

    flip_buffers();

    glUseProgram(0);
}

static void lLoadAllSymbols()
{
    for (unsigned int symbolIndex = 0; symbolIndex < lNumberOfSymbols; ++symbolIndex)
    {
        sCompileSymbol(&shader_symbols[symbolIndex]);

        // TODO(ca) Implement progress tracking for the new loader (will probably just recycle the loading bar section currently used by the loader for gfx/symbolize.py)

        updateBar();
    }
}

static void lLoadAllPrograms()
{
    // TODO(ca) Implement me after adjusting minification/symbolize.py
}

#endif // LOADER_H
