#ifndef GLTK_ANIMATION_H
#define GLTK_ANIMATION_H

#include <BaseAnimation.h>
#include <Transform.h>

// Glm
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace gl {

/**
 * @brief The Animation class
 */
template< typename T >
class Animation : public BaseAnimation
{

public:
    Animation(const T& from, const T& to, T* target);

public:
    virtual void start();
    virtual void update(double dt);

private:
    T m_from;
    T m_to;
    T* m_target;

};

extern template class Animation<glm::vec3>;
extern template class Animation<glm::quat>;
extern template class Animation<Transform>;

}   // namespace gl

#endif
