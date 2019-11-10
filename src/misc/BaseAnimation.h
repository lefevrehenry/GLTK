#ifndef GLTK_BASEANIMATION_H
#define GLTK_BASEANIMATION_H

#include <Transform.h>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


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
    BaseAnimation();
    virtual ~BaseAnimation() = default;

public:
    unsigned int duration() const;
    void setDuration(unsigned int duration);

    EasingType easing() const;
    void setEasing(EasingType easingType);

public:
    virtual bool finished() const;
    virtual void start();

    virtual void update(double dt);

protected:
    unsigned int m_duration;
    double m_elapsed;
    EasingType m_easingType;

};

}   // namespace gl

#endif
