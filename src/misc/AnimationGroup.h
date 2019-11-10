#ifndef GLTK_ANIMATIONGROUP_H
#define GLTK_ANIMATIONGROUP_H

#include <Animation.h>

// Standard Library
#include <memory>
#include <vector>


namespace gl {

class BaseAnimation;

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
    AnimationGroup(AnimationType animationType);
    virtual ~AnimationGroup() = default;

public:
    void addAnimation(std::shared_ptr<BaseAnimation> baseAnimation);

public:
    bool running();

public:
    virtual void start();
    virtual void stop();

public:
    virtual void update(double dt);

protected:
    std::vector< std::shared_ptr<BaseAnimation> > m_animations;
    size_t m_indexAnimation;
    bool m_running;
    AnimationType m_type;

};

}   // namespace gl

#endif
