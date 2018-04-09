#ifndef VISUALMANAGER_H
#define VISUALMANAGER_H

#include "Material.h"
#include "Transform.h"

// Glew
#include <GL/glew.h>

// Standard Library
#include <stack>
#include <vector>


namespace gl {

class ShaderProgram;
class VisualModel;
class VisualOption;

/**
 * @brief The Node class
 */
class Node
{

public:
    Node();
    virtual ~Node();

public:
    Node* addChild();
    Node* removeChild(unsigned int i);

    unsigned int getNbChild() const;
    Node* getChild(unsigned int i) const;

    /* add iterator(s) node/mesh ? */

public:
    void addVisual(const VisualModel* visual);
    void removeVisual(unsigned int i);

    unsigned int getNbVisual() const;
    const VisualModel* getVisual(unsigned int i) const;

public:
    void setShaderProgram(ShaderProgram* shaderProgram);
    void removeShaderProgram();

    ShaderProgram* shaderProgram() const;

public:
    void setVisualOption(VisualOption* visualOption);
    void removeVisualOption();

    VisualOption* visualOption() const;

private:
    std::vector<Node*>              m_children;
    std::vector<const VisualModel*> m_visuals;
    ShaderProgram*                  m_shaderProgram;
    VisualOption*                   m_visualOption;

};

/**
 * @brief The VisualManager class
 */
class VisualManager
{

public:
    VisualManager();
    virtual ~VisualManager();

public:
    void updateUniformBufferTransform(const gl::Transform& transform);
    void updateUniformBufferMaterial(const gl::Material& material);

public:
    void draw(Node* node);

private:
    std::stack<ShaderProgram*>  m_shaderStack;
    std::stack<VisualOption*>   m_optionStack;

    GLuint m_ubo;

};

}   // namespace gl

#endif
