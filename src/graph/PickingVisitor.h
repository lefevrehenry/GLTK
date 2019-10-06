#ifndef PICKINGVISITOR_H
#define PICKINGVISITOR_H

#include "Visitor.h"

// Glm
#include <glm/glm.hpp>

// Standard Library
#include <deque>
#include <memory>


namespace gl {

class Framebuffer;
class Node;
class ShaderProgram;
class VisualModel;

/**
 * @brief The PickingVisitor class
 */
class PickingVisitor : public Visitor
{

public:
    PickingVisitor();

public:
    void set(int x, int y);

public:
    const VisualModel* selectedVisualModel() const;
    glm::vec3 selectedPosition() const;

public:
    virtual void start();
    virtual void end();
    virtual void processNode(const Node* node);

private:
    std::unique_ptr<Framebuffer>    m_pickingFramebuffer;
    std::unique_ptr<ShaderProgram>  m_shaderProgram;

    std::deque<const VisualModel*>  m_visualModels;

    const VisualModel*  m_selectedVisualModel;
    glm::vec3           m_selectedPosition;

    int m_x;
    int m_y;
    unsigned int m_id;

};

}

#endif