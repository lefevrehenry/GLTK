#ifndef GLTK_PARALLELANIMATION_H
#define GLTK_PARALLELANIMATION_H

#include <AnimationGroup.h>


namespace gl {

class BaseAnimation;

/**
 * @brief The ParallelAnimation class
 */
class ParallelAnimation : public AnimationGroup
{

public:
    virtual void start();
    virtual void update(double dt);

};

}   // namespace gl

#endif
