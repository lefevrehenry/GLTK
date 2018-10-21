#ifndef RENDERED_H
#define RENDERED_H

#include "Camera.h"
#include "Scene.h"
#include "Framebuffer.h"
#include "Viewport.h"
#include "Visitor.h"


namespace gl {

/**
 * @brief The Rendered class
 */
struct Rendered
{

public:
    Rendered();

public:
    bool isComplete() const;

    void draw() const;

public:
    SceneGraph* scene;
    Camera* camera;
    Viewport* viewport;
    Framebuffer* framebuffer;
    Visitor* visitor;

};

}   // namespace gl

#endif
