#include "ParallelAnimation.h"

#include <Animation.h>

using namespace gl;

void ParallelAnimation::start() {
    for (BaseAnimation& animation : m_animations)
        animation.start();

    AnimationGroup::start();
}

void ParallelAnimation::update(double dt)
{
    for (BaseAnimation& animation : m_animations) {
        animation.update(dt);

        if(animation.finished() && m_type == Loop)
            animation.start();
    }
}
