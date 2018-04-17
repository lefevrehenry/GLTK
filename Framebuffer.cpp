#include "Framebuffer.h"

#include "Message.h"

using namespace gl;

Framebuffer::Framebuffer(unsigned int width, unsigned int height) :
    m_framebufferId(0),
    m_renderTexture(0),
    m_depthTexture(0),
    m_width(width),
    m_height(height)
{
    glGenFramebuffers(1, &m_framebufferId);
}

Framebuffer::~Framebuffer()
{
    delete m_renderTexture;
    m_renderTexture = nullptr;

    delete m_depthTexture;
    m_depthTexture = nullptr;

    glDeleteFramebuffers(1, &m_framebufferId);
}

void Framebuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId);
}

void Framebuffer::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::attachTexture()
{
    if (m_renderTexture != nullptr) {
        msg_warning("Framebuffer") << "Texture attachement has already been set, no modifications performed";
        return;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId);

    this->m_renderTexture = new Texture();
    this->m_renderTexture->bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_renderTexture->getTextureID(), 0);

//    // ???
//    GLuint tab[] = {GL_COLOR_ATTACHMENT0};
//    glDrawBuffers(1, tab);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::attachDepthTexture()
{
    if (m_depthTexture != nullptr) {
        msg_warning("Framebuffer") << "Depth attachement has already been set, no modifications performed";
        return;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId);

    this->m_depthTexture = new Texture();
    this->m_depthTexture->bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture->getTextureID(), 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
