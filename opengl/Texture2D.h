#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <opengl/Texture.h>

// Standard Library
#include <string>


namespace gl {

/**
 * @brief The Texture2D class
 */
class Texture2D : public Texture
{

public:
    virtual void load(const std::string& filename);

};

}   // namespace gl

#endif
