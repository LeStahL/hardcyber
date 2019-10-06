#ifndef LOADER_H
#define LOADER_H

#include "renderer.h"
#include "shader.h"

// Generated resources
#include "shaders.gen.h"


#define lNumberOfSymbols (ARRAYSIZE(shader_symbols))
#define lNumberOfPrograms (ARRAYSIZE(shader_programs))

#define lLoadProgressStep (0.2f / (lNumberOfSymbols + lNumberOfPrograms))


static float progress = 0.f;


static void lInitializeLoader()
{
    // Load loading bar shader
    sCompileShaderProgram(&shader_program_gfx_load, shader_symbols);
}

#ifdef DEBUG_SHADER
static const char* lGetShaderError()
{
    for (size_t index = 0; index < shader_program_gfx_load.numberOfSymbols; ++index)
    {
        if (shader_symbols[shader_program_gfx_load.symbols[index]].compileStatus != GL_TRUE)
        {
            return shader_symbols[shader_program_gfx_load.symbols[index]].compilerError;
        }
    }

    if (shader_program_gfx_load.linkStatus != GL_TRUE)
    {
        return shader_program_gfx_load.linkerError;
    }

    return NULL;
}
#endif

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
        sCompileSymbol(shader_symbols + symbolIndex);

        progress += lLoadProgressStep;

        updateBar();
    }
}

static void lLoadAllPrograms()
{
    for (unsigned int programIndex = 0; programIndex < lNumberOfPrograms; ++programIndex)
    {
        sCompileShaderProgram(shader_programs + programIndex, shader_symbols);

        progress += lLoadProgressStep;

        updateBar();
    }
}

#endif // LOADER_H
