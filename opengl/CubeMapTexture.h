#ifndef CUBEMAPTEXTURE_H
#define CUBEMAPTEXTURE_H

#include <opengl/Texture.h>

// Standard Library
#include <string>


namespace gl {

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
