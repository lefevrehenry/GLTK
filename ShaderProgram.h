#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

// Standard Library
#include <vector>

// OpenGL
#include <GL/glew.h>


namespace gl {

class Shader;

/**
 * @brief The ShaderProgram class
 */
class ShaderProgram
{

public:
    ShaderProgram();
    virtual ~ShaderProgram();

public:

    GLuint getProgramID() const { return m_programId; }

    bool isLinked() const { return m_isLinked; }

    bool addShader(const Shader& shader);

    void link();

private:

    GLuint m_programId;

    std::vector<const Shader*> m_shaderList;

    bool m_isLinked;

};

}   // namespace gl

#endif
