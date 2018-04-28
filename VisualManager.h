#ifndef VISUALMANAGER_H
#define VISUALMANAGER_H

#include "Camera.h"
#include "Material.h"
#include "Transform.h"

// Glew
#include <GL/glew.h>

// Standard Library
#include <stack>
#include <vector>


namespace gl {

class ShaderProgram;
class Visitor;
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
    void executeVisitor(Visitor* visitor) const;

private:
    void doExecuteVisitor(Visitor* visitor) const;

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
    static void Init();
    static void Clean();

public:
    static void UpdateUniformBufferTransform(const gl::Transform& transform);
    static void UpdateUniformBufferMaterial(const gl::Material& material);
    static void UpdateUniformBufferCamera(const gl::Camera& camera);

private:
    static GLuint m_uboModel;
    static GLuint m_uboCamera;

};

}   // namespace gl

#endif
