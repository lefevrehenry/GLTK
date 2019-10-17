#include "Texture.h"

#include <Data.h>
#include <TexturePrivate.h>

using namespace gl;

Texture::Texture() :
    m_texturePrivate(nullptr)
{

}

void Texture::load(const std::string& filename)
{
    if(!this->m_texturePrivate)
        return;

    this->m_texturePrivate->load(filename);
}

void Texture::bind() const
{
    if(!this->m_texturePrivate)
        return;

    this->m_texturePrivate->bind();
}

void Texture::unbind() const
{
    if(!this->m_texturePrivate)
        return;

    this->m_texturePrivate->unbind();
}

TexturePrivate *Texture::texturePrivate() const
{
    return this->m_texturePrivate.get();
}
