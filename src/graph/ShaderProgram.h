#ifndef GLTK_SHADERPROGRAM_H
#define GLTK_SHADERPROGRAM_H

#include <CubeMapTexture.h>
#include <gltk.h>
#include <Texture2D.h>

// Glm
#include <glm/glm.hpp>

// Standard Library
#include <memory>
#include <string>


namespace gl {

class ShaderProgramPrivate;

/**
 * @brief The ShaderProgram class
 */
class ShaderProgram
{

public:
    using SPtr = std::shared_ptr<ShaderProgram>;

public:
    ShaderProgram();

public:
    std::string vertexShaderCode() const;
    void setVertexShaderCode(const std::string& vertexShaderCode);

    std::string geometryShaderCode() const;
    void setGeometryShaderCode(const std::string& geometryShaderCode);

    std::string fragmentShaderCode() const;
    void setFragmentShaderCode(const std::string& fragmentShaderCode);

public:
    void link();
    bool isLinked() const;

public:
    void attachUniformBufferTransform(const char* name);
    void attachUniformBufferMaterial(const char* name);
    void attachUniformBufferCamera(const char* name);
    void attachUniformBufferLight(const char* name);
    void attachUniformBufferTime(const char* name);

public:
    void setUniformValue(const char* name, float x);
    void setUniformValue(const char* name, const glm::vec2& v);
    void setUniformValue(const char* name, const glm::vec3& v);
    void setUniformValue(const char* name, const glm::vec4& v);
    void setUniformValue(const char* name, const glm::mat2& m);
    void setUniformValue(const char* name, const glm::mat3& m);
    void setUniformValue(const char* name, const glm::mat4& m);
    void setUniformValue(const char* name, Texture2D::SPtr t);
    void setUniformValue(const char* name, CubeMapTexture::SPtr t);

public:
    void bind() const;
    void unbind() const;

private:
    std::shared_ptr<ShaderProgramPrivate> m_shaderProgramPrivate;

    std::string m_vertexShaderCode;
    std::string m_geometryShaderCode;
    std::string m_fragmentShaderCode;

};

}

#endif
