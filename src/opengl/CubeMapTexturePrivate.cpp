#include "CubeMapTexturePrivate.h"

#include <FileRepository.h>
#include <Message.h>

// Glad
#include <glad/glad.h>

// Stb Image
#include <stb_image/stb_image.h>

using namespace gl;

void CubeMapTexturePrivate::bind() const
{
    glActiveTexture(GL_TEXTURE0 + this->m_textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_textureId);
}

void CubeMapTexturePrivate::unbind() const
{
    glActiveTexture(GL_TEXTURE0 + this->m_textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMapTexturePrivate::load(const std::string& filename)
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

void CubeMapTexturePrivate::load(const std::string& left, const std::string& right, const std::string& bottom, const std::string& top, const std::string& back, const std::string& front)
{
    const std::string list[6] = {left, right, bottom, top, back, front};
}
