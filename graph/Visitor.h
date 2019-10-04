#ifndef VISITOR_H
#define VISITOR_H

#include "gltk.h"

// Glm
#include <glm/glm.hpp>

// Standard Library
#include <deque>
#include <list>
#include <memory>
#include <stack>


namespace gl {

class Framebuffer;
class Node;
class Selectable;
class ShaderProgram;
class VisualModel;
class VisualOption;

/**
 * @brief The Visitor class
 */
class Visitor
{

public:
    virtual ~Visitor();

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

protected:
    std::stack<ShaderProgram*>  m_shaderStack;
    std::stack<VisualOption*>   m_optionStack;

    ShaderProgram*  m_currentShader;
    VisualOption*   m_currentOption;

};

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

/**
 * @brief The FetchVisualModelVisitor class
 */
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

/**
 * @brief The ShaderVisitor class
 */
class ShaderVisitor : public DrawVisitor
{

public:
    ShaderVisitor();
    ShaderVisitor(GLTK::ShaderProgramType shaderProgramType);

public:
    virtual void processNode(const Node* node);

public:
   void setShaderProgram(GLTK::ShaderProgramType shaderProgramType);

private:
    std::unique_ptr<ShaderProgram> m_shaderProgram;

};

}   // namespace gl

#endif
