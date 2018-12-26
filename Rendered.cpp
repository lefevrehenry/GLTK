#include "Rendered.h"

#include "Camera.h"
#include "Node.h"
#include "Scene.h"
#include "Visitor.h"
#include "VisualManager.h"

using namespace gl;

static DrawVisitor defaultVisitor;

Rendered::Rendered() :
    scene(nullptr),
    camera(nullptr),
    visitor(nullptr)
{

}

bool Rendered::isComplete() const
{
    return (scene != nullptr && camera != nullptr);
}

void Rendered::draw() const
{
    if (!isComplete())
        return;

    VisualManager::UpdateUniformBufferCamera(*camera);

    Visitor* visitor = (this->visitor != nullptr ? this->visitor : &defaultVisitor);

    Node* node = scene->root();
    node->executeVisitor(visitor);
}
