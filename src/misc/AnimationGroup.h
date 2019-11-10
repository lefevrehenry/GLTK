#ifndef GLTK_ANIMATIONGROUP_H
#define GLTK_ANIMATIONGROUP_H

#include <Animation.h>

// Standard Library
#include <vector>


namespace gl {

/**
 * @brief The AnimationGroup class
 */
class AnimationGroup
{
public:
    enum AnimationType {
        Loop,
        Once
    };

public:
    AnimationGroup();
    virtual ~AnimationGroup() = default;

public:
    void addAnimation(BaseAnimation baseAnimation);

public:
    bool running();

public:
    virtual void start();
    virtual void stop();

public:
    virtual void update(double dt);

protected:
    std::vector<BaseAnimation> m_animations;
    size_t m_indexAnimation;
    bool m_running;
    AnimationType m_type;

};

}   // namespace gl

#endif
