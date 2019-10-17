#include "FetchVisualModelVisitor.h"

#include <Node.h>
#include <VisualModel.h>

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
        std::shared_ptr<const VisualModel> visualModel(node->getVisual(i));
        this->m_visualModels.push_front(visualModel);
    }
}

std::list<std::weak_ptr<const VisualModel>> FetchVisualModelVisitor::getVisualModels() const
{
    return this->m_visualModels;
}
