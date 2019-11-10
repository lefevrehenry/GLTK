#ifndef GLTK_SEQUENTIALANIMATION_H
#define GLTK_SEQUENTIALANIMATION_H

#include <AnimationGroup.h>


namespace gl {

class BaseAnimation;

/**
 * @brief The SequentialAnimation class
 */
class SequentialAnimation : public AnimationGroup
{

public:
    SequentialAnimation(AnimationType animationType);

public:
    virtual void start();
    virtual void update(double dt);

private:
    BaseAnimation* nextAnimation();

};

}   // namespace gl

#endif
