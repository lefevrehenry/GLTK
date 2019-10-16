#ifndef TEXTUREPRIVATE_H
#define TEXTUREPRIVATE_H

// Standard Library
#include <list>
#include <string>

// OpenGL
#include <GL/glew.h>


namespace gl {

/**
 * @brief The TexturePrivate class
 */
class TexturePrivate
{

public:
    TexturePrivate();
    virtual ~TexturePrivate();

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
