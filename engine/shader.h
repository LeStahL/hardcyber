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
#ifdef DEBUG_SHADER
    GLint compileStatus;
    GLint errorLogLength;
    GLchar *compilerError;
#endif
};

struct ShaderProgram
{
    GLuint handle;
    unsigned char numberOfSymbols;
    unsigned char numberOfUniforms;
    const unsigned short* symbols;
    struct Uniform* uniforms;
#ifdef DEBUG_SHADER
    GLint linkStatus;
    GLint errorLogLength;
    GLchar *linkerError;
#endif
};

static void sCompileSymbol(struct ShaderSymbol* symbol)
{
    if (symbol->handle == 0)
    {
        const GLuint shaderHandle = glCreateShader(symbol->type);
        glShaderSource(shaderHandle, 1, &symbol->source, NULL);
        glCompileShader(shaderHandle);
        
#ifdef DEBUG_SHADER
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &symbol->compileStatus);
        if (symbol->compileStatus != GL_TRUE)
        {
            glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &symbol->errorLogLength);
            symbol->compilerError = (GLchar*)malloc(symbol->errorLogLength*sizeof(GLchar));
            glGetShaderInfoLog(shaderHandle, symbol->errorLogLength, NULL, symbol->compilerError);
        }
#endif
        
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
    
#ifdef DEBUG_SHADER
        glGetProgramiv(programHandle, GL_LINK_STATUS, &program->linkStatus);
        if (program->linkStatus != GL_TRUE)
        {
            glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &program->errorLogLength);
            program->linkerError = (GLchar*)malloc(program->errorLogLength*sizeof(GLchar));
            glGetProgramInfoLog(programHandle, program->errorLogLength, NULL, program->linkerError);
        }
#endif
    
    glUseProgram(programHandle);
    
    for (size_t index = 0; index < program->numberOfUniforms; ++index)
    {
        program->uniforms[index].location = glGetUniformLocation(programHandle, program->uniforms[index].name);
    }

    program->handle = programHandle;
}

#endif // SHADER_H
