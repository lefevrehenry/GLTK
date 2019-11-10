#include "BaseAnimation.h"

using namespace gl;

BaseAnimation::BaseAnimation() :
    m_duration(0),
    m_elapsed(0),
    m_easingType(Linear)
{
}

unsigned int BaseAnimation::duration() const
{
    return this->m_duration;
}

void BaseAnimation::setDuration(unsigned int duration)
{
    this->m_duration = duration;
}

BaseAnimation::EasingType BaseAnimation::easing() const
{
    return this-> m_easingType;
}

void BaseAnimation::setEasing(BaseAnimation::EasingType easingType)
{
    this->m_easingType = easingType;
}

bool BaseAnimation::finished() const
{
    return this->m_elapsed == 0.0;
}

void BaseAnimation::start()
{
    this->m_elapsed = m_duration;
}

void BaseAnimation::update(double)
{

}
