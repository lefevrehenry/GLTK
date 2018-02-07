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

private:
    typedef typename ShaderProgram::ShaderProgramType ShaderProgramType;

public:

    Program();
    virtual ~Program();

public:

    unsigned int getNbShaderProgram() const;

    ShaderProgram* getShaderProgram(unsigned int i) const;

    ShaderProgram* addShaderProgram(ShaderProgramType shaderProgramType);

public:

    void draw() const;

private:

    std::vector<ShaderProgram*> m_shaderProgramList;

};

}   // namespace gl

#endif
