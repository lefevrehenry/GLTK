#include "CubeMapTexture.h"

#include <opengl/CubeMapTexturePrivate.h>

using namespace gl;

CubeMapTexture::CubeMapTexture() : Texture()
{
    this->m_texturePrivate.reset(new CubeMapTexturePrivate());
}

CubeMapTexture::CubeMapTexture(const std::string& filename) : Texture()
{
    this->m_texturePrivate.reset(new CubeMapTexturePrivate());
    this->load(filename);
}
