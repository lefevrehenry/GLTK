#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

#include <Visitor.h>

// Standard Library
#include <stack>


namespace gl {

class Node;
class ShaderProgram;

/**
 * @brief The DrawVisitor class
 */
class DrawVisitor : public Visitor
{

public:
    DrawVisitor();
    virtual ~DrawVisitor();

public:
    virtual void start();
    virtual void forwardNode(const Node* node);
    virtual void processNode(const Node* node);
    virtual void backwardNode(const Node* node);

protected:
    std::stack<ShaderProgram*>  m_shaderStack;
    ShaderProgram*  m_currentShader;

};

}

#endif
