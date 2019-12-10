#ifndef GLTK_SHADER_H
#define GLTK_SHADER_H

// Standard Library
#include <string>

// Glad
#include <glad/glad.h>


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

public:
    Shader(ShaderType shaderType);
    virtual ~Shader();

public:
    GLuint getShaderID() const;
    ShaderType getShaderType() const;

    bool isCompiled() const;
    void compileSourceCode(const std::string& sourceCode);

private:
    GLuint      m_shaderId;
    ShaderType  m_shaderType;

    bool        m_isCompiled;
    const char* m_sourceCode;


};

}   // namespace gl

#endif
