#include "AnimationGroup.h"

using namespace gl;

AnimationGroup::AnimationGroup(AnimationType animationType) :
    m_animations(),
    m_indexAnimation(0),
    m_running(false),
    m_type(animationType)
{
}

void AnimationGroup::addAnimation(std::shared_ptr<BaseAnimation> baseAnimation)
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
