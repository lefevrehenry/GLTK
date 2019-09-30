#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "Texture.h"

// Standard Library
#include <vector>


namespace gl {

/**
 * @brief The Framebuffer class
 */
class Framebuffer
{

public:
    Framebuffer(unsigned int width, unsigned int height);
    virtual ~Framebuffer();

public:
    Texture* renderTexture(unsigned int i);
    Texture* depthTexture();

public:
    unsigned int width() const;
    unsigned int height() const;

public:
    void bind() const;
    void unbind() const;

public:
    void attachTexture();
    void attachDepthTexture();
    void attachStencilTexture();

private:
    GLuint m_framebufferId;

    std::vector<Texture*> m_textureList;
    Texture* m_depthTexture;
    Texture* m_stencilTexture;

    unsigned int m_width;
    unsigned int m_height;

};

}   // namespace gl

#endif
