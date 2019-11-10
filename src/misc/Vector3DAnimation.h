#ifndef GLTK_VECTOR3DANIMATION_H
#define GLTK_VECTOR3DANIMATION_H

#include <Animation.h>

// Glm
#include <glm/glm.hpp>


namespace gl {

class Vector3DAnimation : public Animation<glm::vec3>
{

public:
    Vector3DAnimation(const glm::vec3& from, const glm::vec3& to);

};

}   // namespace gl

#endif
