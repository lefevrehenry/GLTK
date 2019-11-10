#ifndef GLTK_ANIMATION_H
#define GLTK_ANIMATION_H

#include <Transform.h>

// Glm
#include <glm/glm.hpp>

// Standard Library
#include <algorithm>


namespace gl {

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


class BaseAnimation
{

public:
    enum EasingType {
        Linear,
        Square,
        Cubic
    };

public:
    BaseAnimation() :
        m_duration(0),
        m_elapsed(0),
        m_easingType(Linear)
    {

    }
    virtual ~BaseAnimation() = default;

public:
    unsigned int duration() const { return this->m_duration; }
    void setDuration(unsigned int duration) { this->m_duration = duration; }

    EasingType easing() const { return this-> m_easingType; }
    void setEasing(EasingType easingType) { m_easingType = easingType; }

public:
    virtual bool finished() const
    {
        return this->m_elapsed == 0.f;
    }

    virtual void start()
    {
        m_elapsed = m_duration;
    }

    virtual void update(float /*dt*/) {}

protected:
    unsigned int m_duration;
    float m_elapsed;
    EasingType m_easingType;

};

template< typename T >
class Animation : public BaseAnimation
{

public:
    Animation(const T& from, const T& to, T* target) :
        m_from(from),
        m_to(to),
        m_target(target)
    {
    }

public:
    virtual void start()
    {
        BaseAnimation::start();

        if (m_duration == 0)
            m_from = m_to;
    }

    virtual void update(float dt)
    {
        if(finished())
            return;

        m_elapsed = std::max(0.f, m_elapsed - dt);

        if(m_target == nullptr)
            return;

        float t = 1.f - (m_elapsed / m_duration);

        *m_target = Animator<T>::mix(m_from, m_to, t);
    }

private:
    T m_from;
    T m_to;
    T* m_target;

};

class Vector3DAnimation : public Animation<glm::vec3>
{
};

class QuaternionAnimation : public Animation<glm::quat>
{
};

class TransformAnimation : public Animation<Transform>
{
};

}   // namespace gl

#endif
