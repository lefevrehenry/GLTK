#include "Texture2D.h"

#include <opengl/TexturePrivate2D.h>

using namespace gl;

Texture2D::Texture2D() : Texture()
{
    this->m_texturePrivate.reset(new TexturePrivate2D());
}

Texture2D::Texture2D(const std::string& filename) : Texture()
{
    this->m_texturePrivate.reset(new TexturePrivate2D());
    this->load(filename);
}
