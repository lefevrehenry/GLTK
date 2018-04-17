#ifndef TEXTURE_H
#define TEXTURE_H

// Standard Library
#include <list>
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
    Texture();
    virtual ~Texture();

public:
    GLuint getTextureID() const;
    unsigned short getTextureUnit() const;

public:
    bool isLoaded() const;
    void load(const std::string& filename);

public:
    void bind() const;
    void unbind() const;

private:
    static std::list<unsigned short> ActiveTexture;

private:
    GLuint m_textureId;
    unsigned short m_textureUnit;
    bool m_isLoaded;

};

}   // namespace gl

#endif
