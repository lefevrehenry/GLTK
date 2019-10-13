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
    virtual ~Node();

public:
    void executeVisitor(Visitor* visitor) const;

private:
    void doExecuteVisitor(Visitor* visitor) const;

public:
    Node* addChild();
    Node* removeChild(unsigned int i);

    size_t getNbChild() const;
    Node* getChild(unsigned int i) const;

    /* add iterator(s) node/mesh ? */

public:
    void addVisual(const VisualModel* visual);
    void removeVisual(unsigned int i);

    size_t getNbVisual() const;
    const VisualModel* getVisual(unsigned int i) const;

public:
    ShaderProgram* shaderProgram() const;
    void setShaderProgram(ShaderProgram* shaderProgram);

private:
    std::vector<Node*>              m_children;
    std::vector<const VisualModel*> m_visuals;
    std::unique_ptr<ShaderProgram>  m_shaderProgram;

};

}   // namespace gl

#endif
