#ifndef NODE_H
#define NODE_H

// Standard Library
#include <memory>
#include <vector>


namespace gl {

class ShaderProgram;
class Visitor;
class VisualModel;

/**
 * @brief The Node class
 */
class Node
{

public:
    Node();

public:
    void executeVisitor(Visitor* visitor) const;

private:
    void doExecuteVisitor(Visitor* visitor) const;

public:
    Node* addChild();
    Node* removeChild(unsigned int i);

    size_t getNbChild() const;
    Node* getChild(unsigned int i) const;

public:
    void addVisual(const VisualModel* visualModel);
    void removeVisual(unsigned int i);

    size_t getNbVisual() const;
    const VisualModel* getVisual(unsigned int i) const;

public:
    ShaderProgram* shaderProgram() const;
    void setShaderProgram(ShaderProgram* shaderProgram);

private:
    std::vector< std::shared_ptr<Node> >                m_children;
    std::vector< std::shared_ptr<const VisualModel> >   m_visuals;
    std::shared_ptr<ShaderProgram>                      m_shaderProgram;

};

}   // namespace gl

#endif
