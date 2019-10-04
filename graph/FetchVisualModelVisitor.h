#ifndef FETCHVISUALMODELVISITOR_H
#define FETCHVISUALMODELVISITOR_H

#include "Visitor.h"

// Standard Library
#include <list>


namespace gl {

class Node;
class VisualModel;

/**
 * @brief The FetchVisualModelVisitor class
 */
class FetchVisualModelVisitor : public Visitor
{

public:
    FetchVisualModelVisitor();
    virtual ~FetchVisualModelVisitor();

public:
    virtual void start();
    virtual void processNode(const Node* node);

public:
    std::list<const VisualModel*> getVisualModels() const;

private:
    std::list<const VisualModel*> m_visualModels;

};

}
#endif
