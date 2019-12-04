#ifndef GLTK_TEXTURE_H
#define GLTK_TEXTURE_H

// Standard Library
#include <memory>
#include <string>


namespace gl {

class TexturePrivate;

/**
 * @brief The Texture class
 */
class Texture
{

public:
    using SPtr = std::shared_ptr<Texture>;

protected:
    Texture();

public:
    void load(const std::string& filename);

public:
    void bind() const;
    void unbind() const;

public:
    std::shared_ptr<TexturePrivate> texturePrivate() const;

protected:
    std::shared_ptr<TexturePrivate> m_texturePrivate;

};

}   // namespace gl

#endif
