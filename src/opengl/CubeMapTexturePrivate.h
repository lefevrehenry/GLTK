#ifndef CUBEMAPTEXTUREPRIVATE_H
#define CUBEMAPTEXTUREPRIVATE_H

#include <opengl/TexturePrivate.h>

// Standard Library
#include <string>


namespace gl {

/**
 * @brief The CubeMapTexturePrivate class
 */
class CubeMapTexturePrivate : public TexturePrivate
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
