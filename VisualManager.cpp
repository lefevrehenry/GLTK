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
    visitor->processNode(this);

    for (unsigned int i = 0; i < this->getNbChild(); ++i) {
        Node* child = this->getChild(i);
        child->doExecuteVisitor(visitor);
    }
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
    m_shaderStack(),
    m_optionStack(),
    m_ubo(0)
{
    size_t size = 2 * sizeof(glm::mat4) + sizeof(float);

    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    this->updateUniformBufferTransform(Transform());
    this->updateUniformBufferMaterial(Material());

    // Bind l'uniform buffer object a l'index 1 dans la table de liaison d'OpenGL
    GLuint binding_ubo_point_index = 1;
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_ubo_point_index, m_ubo);
}

VisualManager::~VisualManager()
{
    glDeleteBuffers(1, &m_ubo);
}

void VisualManager::updateUniformBufferTransform(const Transform& transform)
{
    const glm::mat4& matrix = transform.matrix();
    glBindBuffer(GL_UNIFORM_BUFFER, this->m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(matrix));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void VisualManager::updateUniformBufferMaterial(const Material& material)
{
    const glm::mat4& matrix = material.matrix();
    float shininess = material.shininess();
    glBindBuffer(GL_UNIFORM_BUFFER, this->m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(matrix));
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(float), &shininess);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void VisualManager::draw(Node *node)
{
    // stack the node's ShaderProgram
    ShaderProgram* shaderProgram = node->shaderProgram();
    if (shaderProgram != nullptr)
        m_shaderStack.push(shaderProgram);

    ShaderProgram* topShader = nullptr;

    // get the current shader program
    if (!m_shaderStack.empty())
        topShader = m_shaderStack.top();

//    // stack the node's VisualOption
//    VisualOption* visualOption = node->visualOption();
//    if (visualOption != nullptr)
//        m_optionStack.push(visualOption);

//    VisualOption* topOption = nullptr;

//    // get the current visual option
//    if (!m_optionStack.empty()) {
//        topOption = m_optionStack.top();
//        topOption->push();
//    }

    // bind the current ShaderProgram
    if (topShader != nullptr) {
        topShader->bind();
        topShader->updateDataIfDirty();

        // specifies what kind of primitives has to be drawn by the shader
        PrimitiveMode primitiveMode = topShader->getPrimitiveMode();

        // draw each mesh
        for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
            const VisualModel* visual = node->getVisual(i);
            const Transform& transform = visual->transform();
            const Material& material = visual->material();

            this->updateUniformBufferTransform(transform);
            this->updateUniformBufferMaterial(material);

            visual->draw(primitiveMode);
        }
    }

    // process each child
    for (unsigned int i = 0; i < node->getNbChild(); ++i) {
        Node* child = node->getChild(i);
        this->draw(child);
    }

    // unbind the current ShaderProgram
    if (topShader != nullptr)
        topShader->unbind();

    // unstack the node's ShaderProgram
    if (shaderProgram != nullptr)
        m_shaderStack.pop();

//    // pop the current visual option
//    if (topOption != nullptr)
//        topOption->pop();

//    // unstack the node's visualOption
//    if (visualOption != nullptr)
//        m_optionStack.pop();
}
