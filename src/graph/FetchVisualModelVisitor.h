#ifndef FETCHVISUALMODELVISITOR_H
#define FETCHVISUALMODELVISITOR_H

#include "Visitor.h"

// Standard Library
#include <list>
#include <memory>


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
    std::list<std::weak_ptr<const VisualModel>> getVisualModels() const;

private:
    std::list<std::weak_ptr<const VisualModel>> m_visualModels;

};

}
#endif
