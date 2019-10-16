#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <gltk.h>

// Standard Library
#include <memory>


namespace gl {

class CubeMapTexture;
class ShaderProgramPrivate;
class Texture;

/**
 * @brief The ShaderProgram class
 */
class ShaderProgram
{
    using ShaderProgramType = GLTK::ShaderProgramType;

public:
    using SPtr = std::shared_ptr<ShaderProgram>;

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

public:
    void updateDataIfDirty() const;

    bool addDataTexture(const char* name, Texture* value);
    bool addDataCubeMapTexture(const char* name, CubeMapTexture* value);

private:
    template< typename T >
    bool addData(const char* name, T* value);

private:
    std::shared_ptr<ShaderProgramPrivate> m_shaderProgramPrivate;

};

}

#endif
