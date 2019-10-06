#include "Node.h"

#include <opengl/ShaderProgram.h>
#include <graph/Visitor.h>
#include <opengl/VisualModel.h>
#include <opengl/VisualOption.h>

using namespace gl;

Node::Node() :
    m_children(0),
    m_visuals(0),
    m_shaderProgram(nullptr),
    m_visualOption(nullptr)
{

}

Node::~Node()
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
    if (visual == nullptr)
        return;

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
