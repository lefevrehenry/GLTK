#include "Application.h"

#include "Program.h"
#include "Scene.h"


using namespace gl;

Application::Application() :
    m_scene(0),
    m_programList(0)
{
    // scene
    this->m_scene = new Scene();
}

Application::~Application()
{
    delete this->m_scene;
    this->m_scene = nullptr;

    for (unsigned int i = 0; i < m_programList.size(); ++i) {
        delete m_programList[i];
        m_programList[i] = nullptr;
    }
    m_programList.clear();
}

Scene* Application::getScene()
{
    return this->m_scene;
}

unsigned int Application::getNbProgram() const
{
    return m_programList.size();
}

const Program* Application::getProgram(unsigned int i) const
{
    if (i >= getNbProgram())
        return nullptr;

    return m_programList[i];
}

Program* Application::addProgram()
{
    Program* program = new Program();
    m_programList.push_back(program);
    return program;
}
