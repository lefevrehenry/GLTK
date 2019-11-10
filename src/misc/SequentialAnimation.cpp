#include "SequentialAnimation.h"

#include <Animation.h>

using namespace gl;

void SequentialAnimation::start() {
    this->m_indexAnimation = m_animations.size() - 1;
    AnimationGroup::start();
}

void SequentialAnimation::update(double dt)
{
    if(!running() || m_animations.size() == 0 || m_indexAnimation >= m_animations.size())
        return;

    BaseAnimation* animation = &m_animations.at(m_indexAnimation);

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

    BaseAnimation* animation = &m_animations.at(m_indexAnimation);

    return animation;
}
