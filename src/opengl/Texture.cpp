#include "Texture.h"

#include <helper/FileRepository.h>
#include <helper/Message.h>

// Standard Library
#include <algorithm>

// Stb Image
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

using namespace gl;

std::list<unsigned short> Texture::ActiveTexture;

// find gap in a sequence of number (list must be sorted)
template< typename T >
unsigned short find_gap(const std::list<T>& list)
{
    T next = 1;

    for (auto it = list.begin(); it != list.end(); ++it) {
        if (*it != next)
            return next;
        ++next;
    }

    if (next >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
        msg_error("Texture") << "Max texture unit exceed range of " << GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
        return 0;
    }

    return next;
}

Texture::Texture() :
    m_textureId(0),
    m_textureUnit(0)
{
    glGenTextures(1, &m_textureId);

    unsigned short unit = find_gap<unsigned short>(ActiveTexture);
    auto it = std::upper_bound(ActiveTexture.begin(), ActiveTexture.end(), unit);
    ActiveTexture.insert(it, unit);

    this->m_textureUnit = unit;
}

Texture::~Texture()
{
    auto it = std::find(Texture::ActiveTexture.begin(), Texture::ActiveTexture.end(), this->m_textureUnit);
    if (it != Texture::ActiveTexture.end())
        Texture::ActiveTexture.erase(it);

    glDeleteTextures(1, &m_textureId);
    glActiveTexture(GL_TEXTURE0);
}

GLuint Texture::getTextureID() const
{
    return this->m_textureId;
}

unsigned short Texture::getTextureUnit() const
{
    return this->m_textureUnit;
}

void Texture::bind() const
{
    glActiveTexture(GL_TEXTURE0 + this->m_textureUnit);
    glBindTexture(GL_TEXTURE_2D, this->m_textureId);
}

void Texture::unbind() const
{
    glActiveTexture(GL_TEXTURE0 + this->m_textureUnit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::load(const std::string&)
{
    msg_warning("Texture") << "Texture object can't load a file";
}
