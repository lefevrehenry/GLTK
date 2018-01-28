#include "Shader.h"

#include "Message.h"

// Standard Library
#include <iostream>


using namespace gl;

Shader::Shader(ShaderType shaderType) :
    m_shaderId(0),
    m_shaderType(shaderType),
    m_sourceCode(""),
    m_isCompiled(false)
{
    GLenum type = 0;

    switch (m_shaderType)
    {
    case Vertex:
        type = GL_VERTEX_SHADER;
        break;
    case Geometry:
        type = GL_GEOMETRY_SHADER;
        break;
    case Fragment:
        type = GL_FRAGMENT_SHADER;
        break;
    }

    m_shaderId = glCreateShader(type);
}

Shader::~Shader() {
    glDeleteShader(m_shaderId);
}

void Shader::compileSourceCode(const std::string& sourceCode)
{
    GLint compiled = 0;

    m_sourceCode = sourceCode.c_str();

    glShaderSource(m_shaderId, 1, &m_sourceCode, NULL);
    glCompileShader(m_shaderId);

    glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(m_shaderId, 512, NULL, infoLog);
        msg_error("Shader") << "Compilation failed: " << infoLog;
    }

    m_isCompiled = compiled;
}
