#include "SequentialAnimation.h"

#include <Animation.h>

using namespace gl;

SequentialAnimation::SequentialAnimation(AnimationType animationType) : AnimationGroup(animationType)
{

}

void SequentialAnimation::start() {
    this->m_indexAnimation = 0;

    if(m_indexAnimation < m_animations.size()) {
        BaseAnimation* animation = m_animations.at(m_indexAnimation).get();
        animation->start();
    }

    AnimationGroup::start();
}

void SequentialAnimation::update(double dt)
{
    if(m_animations.size() == 0 || m_indexAnimation >= m_animations.size())
        return;

    BaseAnimation* animation = m_animations.at(m_indexAnimation).get();

    if(animation->finished())
    {
        animation = nextAnimation();

        if(animation == nullptr)
            return;

        animation->start();
    }

    animation->update(dt);
}

BaseAnimation* SequentialAnimation::nextAnimation()
{
    if(m_type == Loop)
        m_indexAnimation = (m_indexAnimation + 1) % m_animations.size();
    else
        m_indexAnimation += 1;

    if(m_indexAnimation >= m_animations.size())
        return nullptr;

    BaseAnimation* animation = m_animations.at(m_indexAnimation).get();

    return animation;
}
