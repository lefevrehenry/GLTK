#include "FrameGraph.h"

#include "FrameObject.h"

using namespace gl;

FrameGraph::FrameGraph() :
    m_rootNode(nullptr)
{

}

FrameGraph::FrameGraph(FrameObject* frameObject) :
    m_rootNode(frameObject)
{

}

FrameGraph::~FrameGraph()
{

}

FrameObject* FrameGraph::root()
{
    return m_rootNode;
}

void FrameGraph::setRoot(FrameObject* frameObject)
{
    this->m_rootNode = frameObject;
}
