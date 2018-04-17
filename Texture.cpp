#include "Texture.h"

#include "Message.h"

// Qt
#include <QImage>
#include <QGLWidget>

// Standard Library
#include <algorithm>

using namespace gl;

std::list<unsigned short> Texture::ActiveTexture;

// find gap in a sequence of number (list must be sorted)
template< typename T >
unsigned short find_gap(const std::list<T>& list)
{
    T next = 0;

    for (auto it = list.begin(); it != list.end(); ++it) {
        if (*it != next)
            return next;
        ++next;
    }

    return next;
}

Texture::Texture() :
    m_textureId(0),
    m_textureUnit(0),
    m_isLoaded(false)
{
    glGenTextures(1, &m_textureId);

    unsigned short unit = find_gap<unsigned short>(ActiveTexture);
    auto it = std::upper_bound(ActiveTexture.begin(), ActiveTexture.end(), unit);
    ActiveTexture.insert(it, unit);

    this->m_textureUnit = unit;
    glActiveTexture(GL_TEXTURE0 + this->m_textureUnit);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_textureId);
    // TODO: deactivate texture unit
}

GLuint Texture::getTextureID() const
{
    return this->m_textureId;
}

unsigned short Texture::getTextureUnit() const
{
    return this->m_textureUnit;
}

bool Texture::isLoaded() const
{
    return this->m_isLoaded;
}

void Texture::load(const std::string& filename)
{
    if (this->m_isLoaded) {
        msg_warning("Texture") << "texture already loaded";
        return;
    }

    if (this->m_textureUnit >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
        msg_error("Texture") << "max texture unit exceed range of " << GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
        return;
    }

    QImage bufferImage = QImage(filename.c_str());

    if (bufferImage.isNull()) {
        msg_error("Texture") << "Unable to load " << filename << " (does file exist ?)";
        return;
    }

    QImage image = QGLWidget::convertToGLFormat(bufferImage);

    if (image.isNull()) {
        msg_error("Texture") << "Unable to convert " << filename << " into readable OpenGL format (extension not supported ?)";
        return;
    }

    glBindTexture(GL_TEXTURE_2D, this->m_textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);

    this->m_isLoaded = true;
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->m_textureId);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
