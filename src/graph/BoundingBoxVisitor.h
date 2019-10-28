#ifndef GLTK_BOUNDINGBOXVISITOR_H
#define GLTK_BOUNDINGBOXVISITOR_H

#include "Visitor.h"

// Glm
#include <glm/glm.hpp>


namespace gl {

class Node;

/**
 * @brief The BoundingBoxVisitor class
 */
class BoundingBoxVisitor : public Visitor
{

public:
    BoundingBoxVisitor();
    virtual ~BoundingBoxVisitor();

public:
    virtual void start();
    virtual void processNode(const Node* node);

public:
    glm::vec3 getMin() const;
    glm::vec3 getMax() const;

private:
    glm::vec3 globalMin;
    glm::vec3 globalMax;

};

}

#endif
