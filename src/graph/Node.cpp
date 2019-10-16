#include "Node.h"

#include <graph/ShaderProgram.h>
#include <graph/Visitor.h>
#include <graph/VisualModel.h>
#include <opengl/VisualOption.h>

using namespace gl;

Node::Node() :
    m_children(0),
    m_visuals(0),
    m_shaderProgram(nullptr)
{

}

void Node::executeVisitor(Visitor* visitor) const
{
    visitor->start();
    this->doExecuteVisitor(visitor);
    visitor->end();
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
    std::shared_ptr<Node> child(new Node());
    this->m_children.push_back(child);

    return child.get();
}

Node* Node::removeChild(unsigned int i)
{
    if (i >= this->m_children.size())
        return nullptr;

    Node* node = getChild(i);
    this->m_children.erase(this->m_children.begin() + i);

    return node;
}

size_t Node::getNbChild() const
{
    return this->m_children.size();
}

Node* Node::getChild(unsigned int i) const
{
    if (i >= getNbChild())
        return nullptr;

    return this->m_children[i].get();
}

void Node::addVisual(const VisualModel* visualModel)
{
    if (visualModel == nullptr)
        return;

    std::shared_ptr<const VisualModel> visual(visualModel);
    this->m_visuals.push_back(visual);
}

void Node::removeVisual(unsigned int i)
{
    if (i >= getNbVisual())
        return;

    this->m_visuals.erase(this->m_visuals.begin() + i);
}

size_t Node::getNbVisual() const
{
    return this->m_visuals.size();
}

const VisualModel* Node::getVisual(unsigned int i) const
{
    if (i >= getNbVisual())
        return nullptr;

    return this->m_visuals[i].get();
}

ShaderProgram* Node::shaderProgram() const
{
    return this->m_shaderProgram.get();
}

void Node::setShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram)
{
    this->m_shaderProgram = shaderProgram;
}
