#include "Shader.h"

#include <Message.h>


using namespace gl;

GLenum ConvertShaderType(Shader::ShaderType shaderType)
{
    switch (shaderType)
    {
    case Shader::Vertex:
        return GL_VERTEX_SHADER;
    case Shader::Geometry:
        return GL_GEOMETRY_SHADER;
    case Shader::Fragment:
        return GL_FRAGMENT_SHADER;
    }
}

Shader::Shader(ShaderType shaderType) :
    m_shaderId(0),
    m_shaderType(shaderType),
    m_isCompiled(false),
    m_sourceCode("")
{
    GLenum type = ConvertShaderType(shaderType);

    m_shaderId = glCreateShader(type);
}

Shader::~Shader()
{
    glDeleteShader(m_shaderId);
}

GLuint Shader::getShaderID() const
{
    return this->m_shaderId;
}

Shader::ShaderType Shader::getShaderType() const
{
    return this->m_shaderType;
}

bool Shader::isCompiled() const
{
    return this->m_isCompiled;
}

void Shader::compileSourceCode(const std::string& sourceCode)
{
    GLint compiled = 0;

    m_sourceCode = sourceCode.c_str();

    glShaderSource(m_shaderId, 1, &m_sourceCode, nullptr);
    glCompileShader(m_shaderId);

    glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(m_shaderId, 512, nullptr, infoLog);
        msg_error("Shader") << "Compilation failed: " << infoLog;
    }

    m_isCompiled = compiled;
}
