#include "BoundingBoxVisitor.h"

#include <Node.h>
#include <Transform.h>
#include <VisualModel.h>

using namespace gl;

BoundingBoxVisitor::BoundingBoxVisitor()
{

}

BoundingBoxVisitor::~BoundingBoxVisitor()
{

}

void BoundingBoxVisitor::start()
{
    float minf = std::numeric_limits<float>::lowest();
    float maxf = std::numeric_limits<float>::max();
    this->globalMin = glm::vec3(maxf, maxf, maxf);
    this->globalMax = glm::vec3(minf, minf, minf);
}

void BoundingBoxVisitor::processNode(const Node* node)
{
    for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
        glm::vec3 min;
        glm::vec3 max;

        std::shared_ptr<const VisualModel> visualModel(node->getVisual(i));
        if(visualModel == nullptr)
            continue;

        visualModel->getBBox(min, max);

        const Transform& transform = visualModel->transform();
        min = glm::vec3(transform.matrix() * glm::vec4(min, 1.0));
        max = glm::vec3(transform.matrix() * glm::vec4(max, 1.0));

        // update globalMin
        globalMin[0] = (min[0] < globalMin[0] ? min[0] : globalMin[0]);
        globalMin[1] = (min[1] < globalMin[1] ? min[1] : globalMin[1]);
        globalMin[2] = (min[2] < globalMin[2] ? min[2] : globalMin[2]);
        // update globalMax
        globalMax[0] = (max[0] > globalMax[0] ? max[0] : globalMax[0]);
        globalMax[1] = (max[1] > globalMax[1] ? max[1] : globalMax[1]);
        globalMax[2] = (max[2] > globalMax[2] ? max[2] : globalMax[2]);
    }
}

glm::vec3 BoundingBoxVisitor::getMin() const
{
    return this->globalMin;
}

glm::vec3 BoundingBoxVisitor::getMax() const
{
    return this->globalMax;
}
