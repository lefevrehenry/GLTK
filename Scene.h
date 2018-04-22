#ifndef SCENE_H
#define SCENE_H

#include "VisualManager.h"


namespace gl {

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

private:
    Node m_rootNode;

};

}   // namespace gl

#endif
