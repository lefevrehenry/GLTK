#include "Framebuffer.h"

#include <Message.h>
#include <TexturePrivate2D.h>

using namespace gl;

Framebuffer::Framebuffer(unsigned int width, unsigned int height) :
    m_framebufferId(0),
    m_textureList(),
    m_depthTexture(nullptr),
    m_stencilTexture(nullptr),
    m_width(width),
    m_height(height)
{
    glGenFramebuffers(1, &m_framebufferId);
}

Framebuffer::~Framebuffer()
{
    for (TexturePrivate* texture : m_textureList) {
        delete texture;
        texture = nullptr;
    }

    m_textureList.clear();

    delete m_depthTexture;
    m_depthTexture = nullptr;

    delete m_stencilTexture;
    m_stencilTexture = nullptr;

    glDeleteFramebuffers(1, &m_framebufferId);
}

TexturePrivate* Framebuffer::renderTexture(unsigned int i)
{
    if (i >= m_textureList.size())
        return nullptr;

    return this->m_textureList[i];
}

TexturePrivate* Framebuffer::depthTexture()
{
    return this->m_depthTexture;
}

unsigned int Framebuffer::width() const
{
    return this->m_width;
}

unsigned int Framebuffer::height() const
{
    return this->m_height;
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
    if (this->m_textureList.size() >= 16) {
        msg_warning("Framebuffer") << "Too many textures have been attached to this framebuffer. No more added";
        return;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId);

    TexturePrivate* texture = new TexturePrivate2D();
    texture->bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, int(m_width), int(m_height), 0, GL_RGBA, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLenum colorAttachement = GL_COLOR_ATTACHMENT0 + m_textureList.size();
    glFramebufferTexture2D(GL_FRAMEBUFFER, colorAttachement, GL_TEXTURE_2D, texture->getTextureID(), 0);

    this->m_textureList.push_back(texture);
    unsigned int size = m_textureList.size();

    GLenum tab[size];
    for (unsigned int i = 0; i < size; ++i)
        tab[i] = GL_COLOR_ATTACHMENT0 + i;

    glDrawBuffers(size, tab);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::attachDepthTexture()
{
    if (m_depthTexture != nullptr) {
        msg_warning("Framebuffer") << "Depth attachement has already been set, no modifications performed";
        return;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId);

    this->m_depthTexture = new TexturePrivate2D();
    this->m_depthTexture->bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, int(m_width), int(m_height), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture->getTextureID(), 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::attachStencilTexture()
{
    msg_warning("Framebuffer") << "not implemented yet";
}
