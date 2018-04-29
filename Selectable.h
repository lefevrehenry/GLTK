#ifndef SELECTABLE_H
#define SELECTABLE_H

// Glm
#include <glm/glm.hpp>


namespace gl {

class VisualModel;

/**
 * @brief The Selectable class
 */
class Selectable
{

public:
    Selectable();
    virtual ~Selectable();

public:
    const VisualModel* visualModel() const;
    void setVisualModel(const VisualModel* visualModel);

    glm::vec4 position() const;
    void setPosition(const glm::vec4& position);

private:
    const VisualModel* m_visualModel;
    glm::vec4 m_position;

};

}   // namespace gl

#endif
