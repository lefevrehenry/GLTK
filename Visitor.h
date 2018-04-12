#ifndef VISITOR_H
#define VISITOR_H

// Glm
#include <glm/glm.hpp>

// Standard Library
#include <stack>


namespace gl {

class Node;
class VisualManager;
class ShaderProgram;
class VisualOption;

/**
 * @brief The Visitor class
 */
class Visitor
{

public:
    virtual void init();
    virtual void forwardNode(const Node* node);
    virtual void processNode(const Node* node) = 0;
    virtual void backwardNode(const Node* node);

};

/**
 * @brief The DrawVisitor class
 */
class DrawVisitor : public Visitor
{

public:
    DrawVisitor(VisualManager* visualManager);
    virtual ~DrawVisitor();

public:
    virtual void init();
    virtual void forwardNode(const Node* node);
    virtual void processNode(const Node* node);
    virtual void backwardNode(const Node* node);

private:
    VisualManager* m_visualManager;

    std::stack<ShaderProgram*>  m_shaderStack;
    std::stack<VisualOption*>   m_optionStack;

    ShaderProgram*  m_currentShader;
    VisualOption*   m_currentOption;

};

/**
 * @brief The BBoxVisitor class
 */
class BBoxVisitor : public Visitor
{

public:
    BBoxVisitor();
    virtual ~BBoxVisitor();

public:
    virtual void init();
    virtual void processNode(const Node* node);

public:
    glm::vec3 getMin() const;
    glm::vec3 getMax() const;

private:
    glm::vec3 globalMin;
    glm::vec3 globalMax;

};

}   // namespace gl

#endif
