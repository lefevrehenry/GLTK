#ifndef GLTK_QUATERNIONDANIMATION_H
#define GLTK_QUATERNIONDANIMATION_H

#include <Animation.h>

// Glm
#include <glm/gtc/quaternion.hpp>


namespace gl {

class QuaternionAnimation : public Animation<glm::quat>
{
};

}   // namespace gl

#endif
