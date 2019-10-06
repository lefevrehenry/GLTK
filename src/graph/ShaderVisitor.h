#ifndef SHADERVISITOR_H
#define SHADERVISITOR_H

#include <graph/DrawVisitor.h>
#include <gltk.h>

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
    ShaderVisitor(GLTK::ShaderProgramType shaderProgramType);

public:
    virtual void processNode(const Node* node);

public:
   void setShaderProgram(GLTK::ShaderProgramType shaderProgramType);

private:
    std::unique_ptr<ShaderProgram> m_shaderProgram;

};

}

#endif
