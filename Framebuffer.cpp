#include "Framebuffer.h"

#include "Mesh.h"
#include "Helper.h"
//#include "Message.h"

using namespace gl;

Framebuffer::Framebuffer(unsigned int width, unsigned int height) :
    m_framebufferId(0),
    m_renderTexture(nullptr),
    m_depthTexture(nullptr),
    m_width(width),
    m_height(height),
    m_vaoQuad(nullptr),
    m_shaderProgram(nullptr)
{
    glGenFramebuffers(1, &m_framebufferId);

    // could be static ?
    this->m_vaoQuad = Mesh::FromFile("models/vaoQuad.obj");

    this->m_shaderProgram = helper::CreateShaderProgram(ShaderProgram::VaoQuad);
}

Framebuffer::~Framebuffer()
{
    delete m_vaoQuad;
    m_vaoQuad = nullptr;

    delete m_shaderProgram;
    m_shaderProgram = nullptr;

    delete m_renderTexture;
    m_renderTexture = nullptr;

    delete m_depthTexture;
    m_depthTexture = nullptr;

    glDeleteFramebuffers(1, &m_framebufferId);
}

Texture* Framebuffer::renderTexture()
{
    return this->m_renderTexture;
}

Texture* Framebuffer::depthTexture()
{
    return this->m_depthTexture;
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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_renderTexture->getTextureID(), 0);

//    // ???
//    GLenum tab[] = {GL_COLOR_ATTACHMENT0};
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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture->getTextureID(), 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::draw(int bounds[4])
{
    // stack the viewport
    GLint initialViewport[4];
    glGetIntegerv(GL_VIEWPORT, &initialViewport[0]);

    int x = bounds[0];
    int y = bounds[1];
    int width = bounds[2];
    int height = bounds[3];

    // set the viewport to draw
    glViewport(x, y, width, height);

    // bind vaoQuad shader
    this->m_shaderProgram->bind();

    int location = glGetUniformLocation(this->m_shaderProgram->getProgramID(), "textureColor");
    glUniform1i(location, m_renderTexture->getTextureUnit());   // i = texture unit to use

    // draw the vaoQuad
    this->m_vaoQuad->draw(PrimitiveMode::TRIANGLES);

    // restore default viewport
    glViewport(initialViewport[0],initialViewport[1],initialViewport[2],initialViewport[3]);
}
