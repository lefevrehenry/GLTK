#ifndef GLTK_TEXTURE2D_H
#define GLTK_TEXTURE2D_H

#include <Texture.h>

// Standard Library
#include <string>


namespace gl {

/**
 * @brief The Texture2D class
 */
class Texture2D : public Texture
{

public:
    using SPtr = std::shared_ptr<Texture2D>;

public:
    Texture2D();
    Texture2D(const std::string& filename);

};

}   // namespace gl

#endif
