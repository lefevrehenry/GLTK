#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "Texture.h"

// Standard Library
#include <vector>

// OpenGL
#include <GL/glew.h>


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

    void attachTexture(unsigned int n);

    void attachDepthTexture();

private:

    GLuint m_framebufferId;
    unsigned int m_width;
    unsigned int m_height;

    std::vector<Texture*> m_renderTextures;
    Texture* m_depthTexture;

};

}   // namespace gl

#endif
