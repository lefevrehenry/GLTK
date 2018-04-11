#include "Visitor.h"

#include "Mesh.h"
#include "Transform.h"
#include "VisualManager.h"
#include "VisualModel.h"

using namespace gl;

DrawVisitor::DrawVisitor()
{

}

DrawVisitor::~DrawVisitor()
{

}

void DrawVisitor::init()
{

}

void DrawVisitor::processNode(const Node* node)
{

}

BBoxVisitor::BBoxVisitor()
{

}

BBoxVisitor::~BBoxVisitor()
{

}

void BBoxVisitor::init()
{
    float minf = std::numeric_limits<float>::lowest();
    float maxf = std::numeric_limits<float>::max();
    this->globalMin = glm::vec3(maxf, maxf, maxf);
    this->globalMax = glm::vec3(minf, minf, minf);
}

void BBoxVisitor::processNode(const Node* node)
{
    for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
        glm::vec3 min;
        glm::vec3 max;

        const VisualModel* visual = node->getVisual(i);
        const Mesh* mesh = visual->mesh();

        mesh->getBbox(min, max);

        const Transform& transform = visual->transform();
        min = glm::vec3(transform.matrix() * glm::vec4(min, 1.0));
        max = glm::vec3(transform.matrix() * glm::vec4(max, 1.0));

        //update globalMin
        globalMin[0] = (min[0] < globalMin[0] ? min[0] : globalMin[0]);
        globalMin[1] = (min[1] < globalMin[1] ? min[1] : globalMin[1]);
        globalMin[2] = (min[2] < globalMin[2] ? min[2] : globalMin[2]);
        // update globalMax
        globalMax[0] = (max[0] > globalMax[0] ? max[0] : globalMax[0]);
        globalMax[1] = (max[1] > globalMax[1] ? max[1] : globalMax[1]);
        globalMax[2] = (max[2] > globalMax[2] ? max[2] : globalMax[2]);
    }
}

glm::vec3 BBoxVisitor::getMin() const
{
    return this->globalMin;
}

glm::vec3 BBoxVisitor::getMax() const
{
    return this->globalMax;
}
