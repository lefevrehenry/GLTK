#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <TexturePrivate.h>

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
    TexturePrivate* renderTexture(unsigned int i);
    TexturePrivate* depthTexture();

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

    std::vector<TexturePrivate*> m_textureList;
    TexturePrivate* m_depthTexture;
    TexturePrivate* m_stencilTexture;

    unsigned int m_width;
    unsigned int m_height;

};

}   // namespace gl

#endif
