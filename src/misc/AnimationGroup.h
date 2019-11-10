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
    AnimationGroup() :
        m_animations(),
        m_indexAnimation(0),
        m_running(true),
        m_type(Loop)
    {
    }
    virtual ~AnimationGroup() = default;

public:
    void addAnimation(BaseAnimation baseAnimation) {
        m_animations.push_back(baseAnimation);
    }

public:
    bool running() {
        return m_running;
    }
    virtual void start() {
        this->m_running = true;
    }
    virtual void stop() {
        this->m_running = false;
    }

public:
    virtual void update(float dt) = 0;

protected:
    std::vector<BaseAnimation> m_animations;
    size_t m_indexAnimation;
    bool m_running;
    AnimationType m_type;

};

}   // namespace gl

#endif
