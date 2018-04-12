#include "VisualManager.h"

#include "ShaderProgram.h"
#include "Visitor.h"
#include "VisualModel.h"
#include "VisualOption.h"

using namespace gl;

Node::Node() :
    m_children(0),
    m_visuals(0),
    m_shaderProgram(nullptr)
{

}

Node::~Node()
{

}

void Node::executeVisitor(Visitor* visitor) const
{
    visitor->init();
    this->doExecuteVisitor(visitor);
}

void Node::doExecuteVisitor(Visitor* visitor) const
{
    visitor->forwardNode(this);
    visitor->processNode(this);

    for (unsigned int i = 0; i < this->getNbChild(); ++i) {
        Node* child = this->getChild(i);
        child->doExecuteVisitor(visitor);
    }

    visitor->backwardNode(this);
}

Node* Node::addChild()
{
    Node* child = new Node();
    this->m_children.push_back(child);
    return child;
}

Node* Node::removeChild(unsigned int i)
{
    if (i >= this->m_children.size())
        return nullptr;

    Node* node = getChild(i);
    this->m_children.erase(this->m_children.begin() + i);

    return node;
}

unsigned int Node::getNbChild() const
{
    return this->m_children.size();
}

Node* Node::getChild(unsigned int i) const
{
    if (i >= getNbChild())
        return nullptr;

    return this->m_children[i];
}

void Node::addVisual(const VisualModel* visual)
{
    this->m_visuals.push_back(visual);
}

void Node::removeVisual(unsigned int i)
{
    if (i >= getNbVisual())
        return;

    this->m_visuals.erase(this->m_visuals.begin() + i);
}

unsigned int Node::getNbVisual() const
{
    return this->m_visuals.size();
}

const VisualModel* Node::getVisual(unsigned int i) const
{
    if (i >= getNbVisual())
        return nullptr;

    return this->m_visuals[i];
}

void Node::setShaderProgram(ShaderProgram* shaderProgram)
{
    this->m_shaderProgram = shaderProgram;
}

void Node::removeShaderProgram()
{
    this->m_shaderProgram = nullptr;
}

ShaderProgram* Node::shaderProgram() const
{
    return this->m_shaderProgram;
}

void Node::setVisualOption(VisualOption* visualOption)
{
    this->m_visualOption = visualOption;
}

void Node::removeVisualOption()
{
    this->m_visualOption= nullptr;
}

VisualOption* Node::visualOption() const
{
    return this->m_visualOption;
}

VisualManager::VisualManager() :
    m_uboModel(0),
    m_uboCamera(0)
{
    // Uniform Buffer Object Model
    glGenBuffers(1, &m_uboModel);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboModel);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + sizeof(float), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    this->updateUniformBufferTransform(Transform());
    this->updateUniformBufferMaterial(Material());

    // Bind l'uniform buffer object a l'index 1 dans la table de liaison d'OpenGL
    GLuint binding_uboModel_point_index = 1;
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_uboModel_point_index, m_uboModel);

    // Uniform Buffer Object Camera
    glGenBuffers(1, &m_uboCamera);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboCamera);
    glBufferData(GL_UNIFORM_BUFFER, 4 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    this->updateUniformBufferCamera(Camera(Camera::Perspective));

    // Bind l'uniform buffer object a l'index 2 dans la table de liaison d'OpenGL
    GLuint binding_uboCamera_point_index = 2;
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_uboCamera_point_index, m_uboCamera);
}

VisualManager::~VisualManager()
{
    glDeleteBuffers(1, &m_uboModel);
}

void VisualManager::updateUniformBufferTransform(const Transform& transform)
{
    const glm::mat4& matrix = transform.matrix();

    glBindBuffer(GL_UNIFORM_BUFFER, this->m_uboModel);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(matrix));

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void VisualManager::updateUniformBufferMaterial(const Material& material)
{
    const glm::mat4& matrix = material.matrix();
    float shininess = material.shininess();

    glBindBuffer(GL_UNIFORM_BUFFER, this->m_uboModel);
    glBufferSubData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(matrix));
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(float), &shininess);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void VisualManager::updateUniformBufferCamera(const Camera& camera)
{
    const glm::mat4& view = camera.view();
    const glm::mat4& projection = camera.projection();
    const glm::mat4& ProjViewMatrix = camera.mvp();
    const glm::mat4& NormalMatrix = glm::mat4(camera.normal());

    glBindBuffer(GL_UNIFORM_BUFFER, this->m_uboCamera);
    glBufferSubData(GL_UNIFORM_BUFFER, 0 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBufferSubData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(ProjViewMatrix));
    glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(NormalMatrix));

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
