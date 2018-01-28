#ifndef SHADER_H
#define SHADER_H

// Standard Library
#include <string>

// OpenGL
#include <GL/glew.h>


namespace gl {

/**
 * @brief The Shader class
 */
class Shader
{

public:

    enum ShaderType {
        Vertex,
        Geometry,
        Fragment
    };

    Shader(ShaderType shaderType);
    virtual ~Shader();

public:

    GLuint getShaderID() const { return m_shaderId; }

    ShaderType getShaderType() const { return m_shaderType; }

    bool isCompiled() const { return m_isCompiled; }

    void compileSourceCode(const std::string& sourceCode);

private:

    GLuint m_shaderId;
    ShaderType m_shaderType;
    const char * m_sourceCode;

    bool m_isCompiled;

};

}   // namespace gl

#endif
