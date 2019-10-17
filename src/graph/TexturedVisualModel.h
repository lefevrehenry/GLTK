#ifndef TEXTUREDVISUALMODEL_H
#define TEXTUREDVISUALMODEL_H

#include <VisualModel.h>

// Standard Library
#include <memory>
#include <string>


namespace gl {

class TexturePrivate2D;

/**
 * @brief The TexturedVisualModel class
 */
class TexturedVisualModel : public VisualModel
{

public:
    TexturedVisualModel(const std::string& filename, const std::string& textureFilename);
    TexturedVisualModel(const TexturedVisualModel& other);

private:
    std::shared_ptr<TexturePrivate2D> m_texture;

};

}   // namespace gl

#endif
