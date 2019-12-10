#include "TexturePrivate2D.h"

#include <FileRepository.h>
#include <Message.h>

// Glad
#include <glad/glad.h>

// Stb Image
#include <stb_image/stb_image.h>

using namespace gl;

void TexturePrivate2D::load(const std::string& filename)
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

    this->bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);

    this->unbind();

    stbi_image_free(data);
}
