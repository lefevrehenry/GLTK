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

/**
 * @brief The Texture2D class
 */
class Texture2D : public Texture
{

public:
    virtual void load(const std::string& filename);

};

/**
 * @brief The CubeMapTexture class
 */
class CubeMapTexture : public Texture
{

public:
    virtual void bind() const;
    virtual void unbind() const;

public:
    virtual void load(const std::string& filename);
    virtual void load(const std::string& left, const std::string& right, const std::string& bottom, const std::string& top, const std::string& back, const std::string& front);

};

}   // namespace gl

#endif
