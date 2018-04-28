#ifndef SCENE_H
#define SCENE_H

#include "VisualManager.h"


namespace gl {

class Visitor;
class VisualModel;

/**
 * @brief The Scene class
 */
class Scene
{

public:
    Scene();
    virtual ~Scene();

public:
    Node* root();
    const Node* root() const;

public:
    void executeVisitor(Visitor* visitor) const;

private:
    Node m_rootNode;

};

}   // namespace gl

#endif
