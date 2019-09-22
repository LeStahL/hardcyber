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

static void lRenderLoadingScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program_gfx_load.handle);
    glUniform2f(shader_uniform_gfx_load_iResolution, w, h);
    glUniform1f(shader_uniform_gfx_load_iProgress, progress);

    quad();
}

#endif // LOADER_H
