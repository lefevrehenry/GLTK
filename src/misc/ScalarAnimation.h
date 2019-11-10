#ifndef GLTK_SCALARANIMATION_H
#define GLTK_SCALARANIMATION_H

#include <Animation.h>


namespace gl {

class ScalarAnimation : public Animation<float>
{

public:
    ScalarAnimation(float from, float to);

};

}   // namespace gl

#endif
