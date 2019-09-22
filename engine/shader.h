#ifndef SHADER_H
#define SHADER_H

#include "platform.h"
#include "renderer.h"


struct Uniform
{
    GLint location;
    const char* name;
};

struct ShaderSymbol
{
    GLuint handle;
    GLuint type;
    const char* source;
};

struct ShaderProgram
{
    GLuint handle;
    unsigned char numberOfSymbols;
    unsigned char numberOfUniforms;
    unsigned short* symbols;
    struct Uniform* uniforms;
};


static void sCompileSymbol(struct ShaderSymbol* symbol)
{
    if (symbol->handle == 0)
    {
        const GLuint shaderHandle = glCreateShader(symbol->type);
        glShaderSource(shaderHandle, 1, &symbol->source, NULL);
        glCompileShader(shaderHandle);

        symbol->handle = shaderHandle;
    }
}

static void sCompileShaderProgram(struct ShaderProgram* program, struct ShaderSymbol* shader_symbols)
{
    const GLuint programHandle = glCreateProgram();

    for (size_t index = 0; index < program->numberOfSymbols; ++index)
    {
        sCompileSymbol(&shader_symbols[program->symbols[index]]);
        glAttachShader(programHandle, shader_symbols[program->symbols[index]].handle);
    }

    glLinkProgram(programHandle);
    glUseProgram(programHandle);

    for (size_t index = 0; index < program->numberOfUniforms; ++index)
    {
        program->uniforms[index].location = glGetUniformLocation(programHandle, program->uniforms[index].name);
    }

    program->handle = programHandle;
}

#endif // SHADER_H
