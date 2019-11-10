#ifndef GLTK_ANIMATION_H
#define GLTK_ANIMATION_H

#include <BaseAnimation.h>
#include <Transform.h>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

// Standard Library
#include <functional>


namespace gl {

/**
 * @brief The Animation class
 */
template< typename T >
class Animation : public BaseAnimation
{

public:
    Animation(const T& from, const T& to);

public:
    void setCallback(std::function<void(const T&)> callback);

public:
    virtual void start();
    virtual void update(double dt);

private:
    T m_from;
    T m_to;

    std::function<void(const T&)> m_callback;

};

extern template class Animation<float>;
extern template class Animation<glm::vec3>;
extern template class Animation<glm::quat>;
extern template class Animation<Transform>;

}   // namespace gl

#endif
