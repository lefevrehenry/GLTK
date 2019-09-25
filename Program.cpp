#include "Program.h"

#include "Helper.h"
#include "Mesh.h"
#include "ShaderProgram.h"

// Glm
#include <glm/gtc/type_ptr.hpp>


using namespace gl;

Program::Program() :
    m_shaderProgramList()
{

}

Program::~Program()
{
    for (ShaderProgram* shaderProgram : this->m_shaderProgramList) {
        delete shaderProgram;
        shaderProgram = nullptr;
    }
}

unsigned int Program::getNbShaderProgram() const
{
    return this->m_shaderProgramList.size();
}

ShaderProgram* Program::getShaderProgram(unsigned int i) const
{
    if (i >= getNbShaderProgram())
        return  nullptr;

    return this->m_shaderProgramList[i];
}

ShaderProgram* Program::addShaderProgram(ShaderProgram::ShaderProgramType shaderProgramType)
{
    ShaderProgram* shaderProgram = ShaderProgram::Create(shaderProgramType);
    m_shaderProgramList.push_back(shaderProgram);
    return shaderProgram;
}

//void Program::draw() const
//{
//    for (unsigned int i = 0; i < getNbShaderProgram(); ++i) {
//        ShaderProgram* shaderProgram = this->m_shaderProgramList[i];
//        shaderProgram->draw();
//    }
//}
