#include "Program.h"

#include "GLFWApplication.h"
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

ShaderProgram* Program::addShaderProgram(ShaderProgramType shaderProgramType)
{
    ShaderProgram* shaderProgram = helper::CreateShaderProgram(shaderProgramType);
    m_shaderProgramList.push_back(shaderProgram);
    return shaderProgram;
}

void Program::draw() const
{
    GLFWApplication* app = GLFWApplication::getInstance();

    for (unsigned int i = 0; i < getNbShaderProgram(); ++i) {
        ShaderProgram* shaderProgram = this->m_shaderProgramList[i];
        GLuint programID = shaderProgram->getProgramID();

        // Bind program
        glUseProgram(programID);

        // update all inputs shader so we can draw safely
        shaderProgram->updateDataIfDirty();

        // Draw
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        app->m_mesh->draw();

        // Unbind program
        glUseProgram(0);
    }
}
