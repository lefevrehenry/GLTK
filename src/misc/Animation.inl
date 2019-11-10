#include "Animation.h"

// Standard Library
#include <algorithm>

using namespace gl;

template< typename T >
class Animator
{
public:
    static T mix(const T& from, const T& to, float t)
    {
        return glm::mix(from, to, t);
    }
};

template<>
class Animator<Transform>
{
public:
    static Transform mix(const Transform& from, const Transform& to, float t)
    {
        return (from * (1.f - t)) * (to * t);
    }
};

template< typename T >
Animation<T>::Animation(const T& from, const T& to) :
    m_from(from),
    m_to(to),
    m_callback()
{
}

template< typename T >
void Animation<T>::setCallback(std::function<void(const T&)> callback)
{
    this->m_callback = callback;
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
    float t = 1.f - (m_elapsed / m_duration);

    T current = Animator<T>::mix(m_from, m_to, t);

    if(this->m_callback)
        this->m_callback(current);
}
