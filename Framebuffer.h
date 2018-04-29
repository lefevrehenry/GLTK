#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "Texture.h"

// Standard Library
#include <vector>

// OpenGL
#include <GL/glew.h>


namespace gl {

class Mesh;
class ShaderProgram;

/**
 * @brief The Framebuffer class
 */
class Framebuffer
{

public:
    Framebuffer(unsigned int width, unsigned int height);
    virtual ~Framebuffer();

public:
    Texture* renderTexture();
    Texture* depthTexture();

public:
    void bind() const;
    void unbind() const;

public:
    void attachTexture();
    void attachDepthTexture();

public:
    void draw(float bounds[4]);

private:
    GLuint m_framebufferId;

    Texture* m_renderTexture;
    Texture* m_depthTexture;

    unsigned int m_width;
    unsigned int m_height;

    Mesh* m_vaoQuad;
    ShaderProgram* m_shaderProgram;
};

}   // namespace gl

#endif
