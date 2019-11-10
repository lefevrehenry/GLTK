#include "AnimationGroup.h"

using namespace gl;

AnimationGroup::AnimationGroup() :
    m_animations(),
    m_indexAnimation(0),
    m_running(true),
    m_type(Loop)
{
}

void AnimationGroup::addAnimation(BaseAnimation baseAnimation)
{
    m_animations.push_back(baseAnimation);
}

bool AnimationGroup::running()
{
    return m_running;
}

void AnimationGroup::start()
{
    this->m_running = true;
}

void AnimationGroup::stop()
{
    this->m_running = false;
}

void AnimationGroup::update(double /*dt*/)
{

}
