#ifndef VISITOR_H
#define VISITOR_H

// Glm
#include <glm/glm.hpp>

// Standard Library
#include <deque>
#include <list>
#include <stack>

namespace gl {

class Framebuffer;
class Node;
class ShaderProgram;
class VisualModel;
class VisualOption;

/**
 * @brief The Visitor class
 */
class Visitor
{

public:
    virtual void start();
    virtual void end();
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
    DrawVisitor();
    virtual ~DrawVisitor();

public:
    virtual void start();
    virtual void forwardNode(const Node* node);
    virtual void processNode(const Node* node);
    virtual void backwardNode(const Node* node);

private:
    std::stack<ShaderProgram*>  m_shaderStack;
    std::stack<VisualOption*>   m_optionStack;

    ShaderProgram*  m_currentShader;
    VisualOption*   m_currentOption;

};

/**
 * @brief The PickingVisitor class
 */
class PickingVisitor : public Visitor
{

public:
    PickingVisitor(unsigned int x, unsigned int y);
    virtual ~PickingVisitor();

public:
    virtual void start();
    virtual void end();
    //virtual void forwardNode(const Node* node);
    virtual void processNode(const Node* node);
    //virtual void backwardNode(const Node* node);

private:
    unsigned int m_x;
    unsigned int m_y;

    Framebuffer* m_pickingFramebuffer;
    ShaderProgram* m_shaderProgram;

    unsigned int m_id;

    std::deque<const VisualModel*> m_visualModels;

};

/**
 * @brief The BoundingBoxVisitor class
 */
class BoundingBoxVisitor : public Visitor
{

public:
    BoundingBoxVisitor();
    virtual ~BoundingBoxVisitor();

public:
    virtual void start();
    virtual void processNode(const Node* node);

public:
    glm::vec3 getMin() const;
    glm::vec3 getMax() const;

private:
    glm::vec3 globalMin;
    glm::vec3 globalMax;

};

class FetchVisualModelVisitor : public Visitor
{

public:
    FetchVisualModelVisitor();
    virtual ~FetchVisualModelVisitor();

public:
    virtual void start();
    virtual void processNode(const Node* node);

public:
    std::list<const VisualModel*> getVisualModels() const;

private:
    std::list<const VisualModel*> m_visualModels;

};

}   // namespace gl

#endif
