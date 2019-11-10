#include "Animation.h"

// Standard Library
#include <algorithm>

using namespace gl;

template< typename T >
Animation<T>::Animation(const T& from, const T& to, T* target) :
    m_from(from),
    m_to(to),
    m_target(target)
{
}

template< typename T >
void Animation<T>::start()
{
    BaseAnimation::start();

    if (m_duration == 0)
        m_from = m_to;
}

template< typename T >
void Animation<T>::update(double dt)
{
    if(finished())
        return;

    m_elapsed = std::max(0.0, m_elapsed - dt);

    if(m_target == nullptr)
        return;

    float t = 1.f - (m_elapsed / m_duration);

    *m_target = Animator<T>::mix(m_from, m_to, t);
}
