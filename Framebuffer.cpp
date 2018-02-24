#include "Framebuffer.h"

#include "Message.h"

using namespace gl;

Framebuffer::Framebuffer(unsigned int width, unsigned int height) :
    m_framebufferId(0),
    m_width(width),
    m_height(height),
    m_renderTextures(0),
    m_depthTexture(0)
{
    glGenFramebuffers(1, &m_framebufferId);
}

Framebuffer::~Framebuffer()
{
    for (Texture* texture : m_renderTextures) {
        delete texture;
        texture = nullptr;
    }
    m_renderTextures.clear();
    delete m_depthTexture;
    m_depthTexture = nullptr;
    glDeleteFramebuffers(1, &m_framebufferId);
}

void Framebuffer::attachTexture(unsigned int n)
{
    if (m_renderTextures.size() > 0) {
        msg_warning("Framebuffer") << "Textures have been already set, no modifications performed";
        return;
    }

    m_renderTextures.resize(n);

    for (unsigned int i = 0; i < n; ++i) {
        Texture* texture = new Texture(i);
        m_renderTextures.push_back(texture);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId);

    glGenTextures(n, &m_renderTextures);

    glBindTexture(GL_TEXTURE_2D, m_renderTextures);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_renderTextures, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::attachDepthTexture()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId);

    glGenTextures(1, &m_depthTexture);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
