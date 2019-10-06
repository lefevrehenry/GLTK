#ifndef DRAWWITHSELECTIONVISITOR_H
#define DRAWWITHSELECTIONVISITOR_H

#include <graph/DrawVisitor.h>

// Standard Library
#include <memory>


namespace gl {

class Node;
class ShaderProgram;
class VisualModel;

/**
 * @brief The DrawVisitorWithSelection class
 */
class DrawVisitorWithSelection : public DrawVisitor
{

public:
    DrawVisitorWithSelection();

public:
    virtual void start();
    virtual void forwardNode(const Node* node);
    virtual void backwardNode(const Node* node);

private:
    std::unique_ptr<ShaderProgram>  m_outlineShader;
    const VisualModel*              m_selected;

};

}

#endif
