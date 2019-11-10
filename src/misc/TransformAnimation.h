#ifndef GLTK_TRANSFORMANIMATION_H
#define GLTK_TRANSFORMANIMATION_H

#include <Animation.h>
#include <Transform.h>


namespace gl {

class TransformAnimation : public Animation<Transform>
{

public:
    TransformAnimation(const Transform& from, const Transform& to);

};

}   // namespace gl

#endif
