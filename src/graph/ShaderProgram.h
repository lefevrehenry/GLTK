#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <gltk.h>

// Standard Library
#include <memory>


namespace gl {

class ShaderProgramPrivate;

/**
 * @brief The ShaderProgram class
 */
class ShaderProgram
{
    using ShaderProgramType = GLTK::ShaderProgramType;

public:
    static ShaderProgram* Create(ShaderProgramType shaderProgramType);

private:
    ShaderProgram();
    ShaderProgram(ShaderProgramPrivate* shaderProgramPrivate);

private:
    ShaderProgramPrivate* shaderProgramPrivate() const;
    void setShaderProgramPrivate(ShaderProgramPrivate* shaderProgramPrivate);

public:
    void bind() const;
    void unbind() const;

    void updateDataIfDirty() const;

private:
    std::shared_ptr<ShaderProgramPrivate> m_shaderProgramPrivate;

};

}

#endif
