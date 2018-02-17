#ifndef TEXTURE_H
#define TEXTURE_H

// Standard Library
#include <string>

// OpenGL
#include <GL/glew.h>


namespace gl {

/**
 * @brief The Texture class
 */
class Texture
{

public:

    Texture(unsigned int textureUnit);
    virtual ~Texture();

public:

    GLuint getTextureID() const;

    unsigned short getTextureUnit() const;

    bool isLoaded() const;

    void load(const std::string& filename);

public:

    void bindTexture() const;

    void unbindTexture() const;

private:

    GLuint m_textureId;

    unsigned short m_textureUnit;

    bool m_isLoaded;

};

}   // namespace gl

#endif
