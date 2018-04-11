#ifndef VISITOR_H
#define VISITOR_H

// Glm
#include <glm/glm.hpp>


namespace gl {

class Node;

/**
 * @brief The Visitor class
 */
class Visitor
{

public:
    virtual void init() = 0;
    virtual void processNode(const Node* node) = 0;

};

/**
 * @brief The DrawVisitor class
 */
class DrawVisitor : public Visitor
{

public:
    DrawVisitor();
    virtual ~DrawVisitor();

public:
    virtual void init();
    virtual void processNode(const Node* node);

};

/**
 * @brief The BBoxVisitor class
 */
class BBoxVisitor : public Visitor
{

public:
    BBoxVisitor();
    virtual ~BBoxVisitor();

public:
    virtual void init();
    virtual void processNode(const Node* node);

public:
    glm::vec3 getMin() const;
    glm::vec3 getMax() const;

private:
    glm::vec3 globalMin;
    glm::vec3 globalMax;

};

}   // namespace gl

#endif
