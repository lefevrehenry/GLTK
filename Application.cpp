#include "Application.h"


using namespace gl;

Application::Application() :
    m_shaderList(0)
{

}

Application::~Application()
{

}

unsigned int Application::getNbProgram() const
{
    return m_shaderList.size();
}

const Program* Application::getProgram(unsigned int i) const
{
    if (i >= getNbProgram())
        return nullptr;

    return m_shaderList[i];
}

void Application::addProgram(const Program& program)
{
    m_shaderList.push_back(&program);
}
