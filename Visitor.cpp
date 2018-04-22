#include "Visitor.h"

#include "Helper.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "VisualManager.h"
#include "VisualModel.h"
#include "VisualOption.h"


using namespace gl;

void Visitor::init()
{

}

void Visitor::forwardNode(const Node* node)
{

}

void Visitor::backwardNode(const Node* node)
{

}

DrawVisitor::DrawVisitor(VisualManager* visualManager) :
    m_visualManager(visualManager),
    m_shaderStack(),
    m_optionStack(),
    m_currentShader(nullptr),
    m_currentOption(nullptr)
{

}

DrawVisitor::~DrawVisitor()
{

}

void DrawVisitor::init()
{
    this->m_currentShader = nullptr;
    this->m_currentOption = nullptr;
}
void DrawVisitor::forwardNode(const Node *node)
{
    ShaderProgram* shaderProgram = node->shaderProgram();

    // stack the node's ShaderProgram
    if (shaderProgram != nullptr)
        m_shaderStack.push(shaderProgram);

    // get the current shader program
    if (!m_shaderStack.empty())
        m_currentShader = m_shaderStack.top();

//    // stack the node's VisualOption
//    VisualOption* visualOption = node->visualOption();
//    if (visualOption != nullptr)
//        m_optionStack.push(visualOption);

//    VisualOption* m_currentOption = nullptr;

//    // get the current visual option
//    if (!m_optionStack.empty()) {
//        m_currentOption = m_optionStack.top();
//        m_currentOption->push();
//    }
}

void DrawVisitor::processNode(const Node* node)
{
    // bind the current ShaderProgram
    if (m_currentShader != nullptr) {
        m_currentShader->bind();
        m_currentShader->updateDataIfDirty();

        // fetch what kind of primitives has to be drawn by the shader
        PrimitiveMode primitiveMode = m_currentShader->getPrimitiveMode();

        // draw each mesh
        for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
            const VisualModel* visual = node->getVisual(i);
            const Transform& transform = visual->transform();
            const Material& material = visual->material();

            this->m_visualManager->updateUniformBufferTransform(transform);
            this->m_visualManager->updateUniformBufferMaterial(material);

            visual->draw(primitiveMode);
        }
    }
}

void DrawVisitor::backwardNode(const Node *node)
{
    ShaderProgram* shaderProgram = node->shaderProgram();

    // unbind the current ShaderProgram
    if (m_currentShader != nullptr)
        m_currentShader->unbind();

    // unstack the node's ShaderProgram
    if (shaderProgram != nullptr)
        m_shaderStack.pop();

//    // pop the current visual option
//    if (m_currentOption != nullptr)
//        m_currentOption->pop();

//    // unstack the node's visualOption
//    if (visualOption != nullptr)
//        m_optionStack.pop();
}

PickingVisitor::PickingVisitor() :
    m_shaderProgram(0),
    m_camera(),
    m_id(0)
{
    this->m_shaderProgram = helper::CreateShaderProgram(ShaderProgram::HighLight);
}

PickingVisitor::~PickingVisitor()
{
    delete m_shaderProgram;
    m_shaderProgram = nullptr;
}

void PickingVisitor::setCamera(const glm::mat4& matrix)
{
    this->m_camera = glm::mat4(matrix);
}

void PickingVisitor::init()
{
    this->m_id = 1;

//    // create shader here
//    if (this->m_shaderProgram == nullptr)

    m_shaderProgram->bind();

//    // send camera here
//    Data<glm::mat4>* camera = this->m_shaderProgram->getDataByName<glm::mat4>("camera");
//    camera->setValue(this->m_camera);

//    m_shaderProgram->updateDataIfDirty();
}

void PickingVisitor::processNode(const Node* node)
{
    if (this->m_shaderProgram != nullptr) {

        // fetch what kind of primitives has to be drawn by the shader
        PrimitiveMode primitiveMode = m_shaderProgram->getPrimitiveMode();

        // draw each mesh
        for (unsigned int i = 0; i < node->getNbVisual(); ++i) {
            const VisualModel* visual = node->getVisual(i);
            //const Transform& transform = visual->transform();

            //this->m_shaderProgram->setUniformValue("transform", transform.matrix());
            //this->m_shaderProgram->setUniformValue("id", this->m_id);

            visual->draw(primitiveMode);

            this->m_id += 1;
        }
    }
}

BoundingBoxVisitor::BoundingBoxVisitor()
{

}

BoundingBoxVisitor::~BoundingBoxVisitor()
{

}

void BoundingBoxVisitor::init()
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

glm::vec3 BoundingBoxVisitor::getMin() const
{
    return this->globalMin;
}

glm::vec3 BoundingBoxVisitor::getMax() const
{
    return this->globalMax;
}
