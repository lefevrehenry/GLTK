#ifndef TEXTUREDVISUALMODEL_H
#define TEXTUREDVISUALMODEL_H

#include <graph/VisualModel.h>

// Standard Library
#include <memory>
#include <string>


namespace gl {

class Texture2D;

/**
 * @brief The TexturedVisualModel class
 */
class TexturedVisualModel : public VisualModel
{

public:
    TexturedVisualModel(const std::string& filename, const std::string& textureFilename);
    TexturedVisualModel(const TexturedVisualModel& other);

private:
    std::shared_ptr<Texture2D> m_texture;

};

}   // namespace gl

#endif
