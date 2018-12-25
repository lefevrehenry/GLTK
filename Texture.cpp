#include "Texture.h"

#include "FileRepository.h"
#include "Message.h"

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

void Texture2D::load(const std::string& filename)
{
    std::string path(filename);

    if (!helper::DataRepository.findFile(path)) {
        msg_error("Texture") << "File " << filename << " not found";
        return;
    }

    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
    channels = 4;

    if (data == nullptr) {
        msg_error("Texture2D") << "image " << filename << " not loaded";
        return;
    }

    glActiveTexture(GL_TEXTURE0 + this->m_textureUnit);

    glBindTexture(GL_TEXTURE_2D, this->m_textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void CubeMapTexture::bind() const
{
    glActiveTexture(GL_TEXTURE0 + this->m_textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_textureId);
}

void CubeMapTexture::unbind() const
{
    glActiveTexture(GL_TEXTURE0 + this->m_textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMapTexture::load(const std::string& filename)
{
    std::string path(filename);

    if (!helper::DataRepository.findFile(path)) {
        msg_error("Texture") << "File " << filename << " not found";
        return;
    }

    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
    channels = 4;

    if (data == nullptr) {
        msg_error("Texture2D") << "image " << filename << " not loaded";
        return;
    }

    int sw = width / 4;
    int sh = height / 3;

    unsigned char* subset_data = new unsigned char[sw * sh * channels];

    int map[6][2] = {
        {2 * sw, 1 * sh},        // Right
        {0 * sw, 1 * sh},        // Left
        {1 * sw, 0 * sh},        // Top
        {1 * sw, 2 * sh},        // Bottom
        {1 * sw, 1 * sh},        // Front
        {3 * sw, 1 * sh}         // Back
    };

    glActiveTexture(GL_TEXTURE0 + this->m_textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_textureId);

    for (unsigned int i = 0; i < 6; ++i) {
        int ox = map[i][0];
        int oy = map[i][1];
        int offset = ((oy * width) + ox) * channels;

        for (int h = 0; h < sh; ++h) {
            unsigned char* src_first = data + (offset + (h * width) * channels);
            unsigned char* src_last = data + (offset + (h * width + sw) * channels);
            unsigned char* dest = subset_data + ((h * sw) * channels);
            std::copy(src_first, src_last, dest);
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGBA32F, sw, sh, 0, GL_RGBA, GL_UNSIGNED_BYTE, subset_data);
    }

    delete[] subset_data;

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    stbi_image_free(data);
}

void CubeMapTexture::load(const std::string& left, const std::string& right, const std::string& bottom, const std::string& top, const std::string& back, const std::string& front)
{
    const std::string list[6] = {left, right, bottom, top, back, front};
}
