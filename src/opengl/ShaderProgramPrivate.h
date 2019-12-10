#ifndef GLTK_SHADERPROGRAMPRIVATE_H
#define GLTK_SHADERPROGRAMPRIVATE_H

#include <gltk.h>
#include <OpenGLAttribute.h>
#include <RenderState.h>
#include <TexturePrivate.h>

// Standard Library
#include <string>

// Glm
#include <glm/glm.hpp>


namespace gl {

/**
 * @brief The ShaderProgramPrivate class
 */
class ShaderProgramPrivate
{
    using ShaderProgramType = GLTK::ShaderProgramType;

public:
    ShaderProgramPrivate();
    virtual ~ShaderProgramPrivate();

public:
    GLuint getProgramID() const;

public:
    void link(const std::string& vs, const std::string& gs, const std::string& fs);
    bool isLinked() const;

public:
    void bind() const;
    void unbind() const;

public:
    bool attachUniformBlock(const char* name, unsigned int binding_index);

public:
    int attributLocation(const char* name) const;

    void setUniformValue(const char* name, int x);
    void setUniformValue(int attributLocation, int x);

    void setUniformValue(const char* name, float x);
    void setUniformValue(int attributLocation, float x);

    void setUniformValue(const char* name, const glm::vec2& v);
    void setUniformValue(int attributLocation, const glm::vec2& v);

    void setUniformValue(const char* name, const glm::vec3& v);
    void setUniformValue(int attributLocation, const glm::vec3& v);

    void setUniformValue(const char* name, const glm::vec4& v);
    void setUniformValue(int attributLocation, const glm::vec4& v);

    void setUniformValue(const char* name, const glm::mat2& m);
    void setUniformValue(int attributLocation, const glm::mat2& m);

    void setUniformValue(const char* name, const glm::mat3& m);
    void setUniformValue(int attributLocation, const glm::mat3& m);

    void setUniformValue(const char* name, const glm::mat4& m);
    void setUniformValue(int attributLocation, const glm::mat4& m);

    void setUniformValue(const char* name, TexturePrivate::SPtr t);
    void setUniformValue(int attributLocation, TexturePrivate::SPtr t);

public:
    template< AttributeName N >
    void setRenderState(typename OpenGL<N>::Type value)
    {
        this->m_renderState.setState<N>(value);
    }

private:
    void pushAttribute() const;
    void popAttribute() const;

private:
    GLuint m_programId;
    bool m_isLinked;

    RenderSate m_renderState;    // change OpenGLStateMachine

};

}   // namespace gl

#endif
