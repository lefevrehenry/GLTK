#ifndef GLTK_BASEANIMATION_H
#define GLTK_BASEANIMATION_H

#include <Transform.h>


namespace gl {

/**
 * @brief The BaseAnimation class
 */
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
