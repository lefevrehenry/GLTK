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
    virtual void update(float dt);

};

}   // namespace gl

#endif
