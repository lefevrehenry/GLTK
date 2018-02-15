#ifndef PROGRAM_H
#define PROGRAM_H

#include "ShaderProgram.h"

// Standard Library
#include <vector>


namespace gl {

class Shader;

class ShaderProgram;

/**
 * @brief The Program class
 */
class Program
{

public:

    enum PolygonMode {
        POINT = GL_POINT,
        LINE = GL_LINE,
        FILL = GL_FILL
    };

    Program();
    virtual ~Program();

public:

    unsigned int getNbShaderProgram() const;

    ShaderProgram* getShaderProgram(unsigned int i) const;

    ShaderProgram* addShaderProgram(ShaderProgram::ShaderProgramType shaderProgramType);

public:

    PolygonMode getPolygonMode();

    void setPolygonMode(PolygonMode polygonMode);

public:

    void draw() const;

private:

    std::vector<ShaderProgram*> m_shaderProgramList;
    PolygonMode m_polygonMode;

};

}   // namespace gl

#endif
