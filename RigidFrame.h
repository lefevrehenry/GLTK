#ifndef RIGIDFRAME_H
#define RIGIDFRAME_H

#include "Mesh.h"

// Standard Library
//#include <string>
//#include <vector>

// Glm
//#include <glm/glm.hpp>

// OpenGL
//#include <GL/glew.h>


namespace gl {

/**
 * @brief The Mesh class
 */
class RigidFrame : private Mesh
{

public:

    RigidFrame();
    virtual ~RigidFrame();

public:

    virtual void draw() const;

};

}   // namespace gl

#endif
