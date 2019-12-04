#ifndef GLTK_TEXTUREPRIVATE2D_H
#define GLTK_TEXTUREPRIVATE2D_H

#include <TexturePrivate.h>

// Standard Library
#include <string>


namespace gl {

/**
 * @brief The TexturePrivate2D class
 */
class TexturePrivate2D : public TexturePrivate
{

public:
    using SPtr = std::shared_ptr<TexturePrivate2D>;

public:
    virtual void load(const std::string& filename);

};

}   // namespace gl

#endif
