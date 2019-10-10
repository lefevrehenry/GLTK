#include "FetchVisualModelVisitor.h"

#include <graph/Node.h>
#include <graph/VisualModel.h>

using namespace gl;

FetchVisualModelVisitor::FetchVisualModelVisitor() :
    m_visualModels()
{

}

FetchVisualModelVisitor::~FetchVisualModelVisitor()
{

}

void FetchVisualModelVisitor::start()
{
    this->m_visualModels.clear();
}

void FetchVisualModelVisitor::processNode(const Node* node)
{
    for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
        const VisualModel* visual = node->getVisual(i);
        this->m_visualModels.push_front(visual);
    }
}

std::list<const VisualModel*> FetchVisualModelVisitor::getVisualModels() const
{
    return this->m_visualModels;
}
