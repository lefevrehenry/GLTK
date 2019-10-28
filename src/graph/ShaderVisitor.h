#ifndef GLTK_SHADERVISITOR_H
#define GLTK_SHADERVISITOR_H

#include <DrawVisitor.h>

// Standard Library
#include <memory>


namespace gl {

class Node;
class ShaderProgram;

/**
 * @brief The ShaderVisitor class
 */
class ShaderVisitor : public DrawVisitor
{

public:
    ShaderVisitor();
    ShaderVisitor(ShaderProgram* shaderProgram);

public:
    virtual void processNode(const Node* node);

public:
    ShaderProgram* shaderProgram() const;
    void setShaderProgram(ShaderProgram* shaderProgram);

private:
    std::unique_ptr<ShaderProgram> m_shaderProgram;

};

}

#endif
