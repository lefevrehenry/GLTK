#include "Texture.h"

#include "FileRepository.h"
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

QImage getQImageFromFile(const std::string& filename)
{
    std::string path(filename);

    if (!helper::DataRepository.findFile(path)) {
        msg_error("Texture") << "File " << filename << " not found";
        return QImage();
    }

    QImage bufferImage = QImage(path.c_str());

    if (bufferImage.isNull()) {
        msg_error("Texture") << "Unable to load " << filename << " (does file exist ?)";
        return QImage();
    }

    QImage image = QGLWidget::convertToGLFormat(bufferImage);

    if (image.isNull()) {
        msg_error("Texture") << "Unable to convert " << filename << " into readable OpenGL format (extension not supported ?)";
        return QImage();
    }

    // flip image vertically
    image = image.mirrored();

    return image;
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
    QImage image = getQImageFromFile(filename);

    if (image.isNull()) {
        msg_error("Texture2D") << "image " << filename << " not loaded";
        return;
    }

    glActiveTexture(GL_TEXTURE0 + this->m_textureUnit);

    glBindTexture(GL_TEXTURE_2D, this->m_textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);
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
    QImage image = getQImageFromFile(filename);

    if (image.isNull()) {
        msg_error("CubeMapTexture") << "image " << filename << " not loaded";
        return;
    }

    int width = image.width() / 4;
    int height = image.height() / 3;

    int map[6][2] = {
        {2 * width, 1 * height},        // Right
        {0 * width, 1 * height},        // Left
        {1 * width, 0 * height},        // Top
        {1 * width, 2 * height},        // Bottom
        {1 * width, 1 * height},        // Front
        {3 * width, 1 * height}         // Back
    };

    glActiveTexture(GL_TEXTURE0 + this->m_textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_textureId);

    for (unsigned int i = 0; i < 6; ++i) {
        int ox = map[i][0];
        int oy = map[i][1];
        QImage crop = image.copy(ox, oy, width, height);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, crop.bits());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}

void CubeMapTexture::load(const std::string& left, const std::string& right, const std::string& bottom, const std::string& top, const std::string& back, const std::string& front)
{
    const std::string list[6] = {left, right, bottom, top, back, front};
}
