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
    virtual void bind() const;
    virtual void unbind() const;

public:
    virtual void load(const std::string& filename);

private:
    static std::list<unsigned short> ActiveTexture;

protected:
    GLuint m_textureId;
    unsigned short m_textureUnit;

};

}   // namespace gl

#endif
