#ifndef VISITOR_H
#define VISITOR_H


namespace gl {

class Node;

/**
 * @brief The Visitor class
 */
class Visitor
{

public:
    virtual ~Visitor();

public:
    virtual void start();
    virtual void end();
    virtual void forwardNode(const Node* node);
    virtual void processNode(const Node* node) = 0;
    virtual void backwardNode(const Node* node);

};

}   // namespace gl

#endif
