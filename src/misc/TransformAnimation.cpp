#include "TransformAnimation.h"

using namespace gl;

TransformAnimation::TransformAnimation(const gl::Transform& from, const gl::Transform& to) : Animation<Transform> (from, to)
{

}
