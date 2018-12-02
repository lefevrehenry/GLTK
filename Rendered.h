#ifndef RENDERED_H
#define RENDERED_H


namespace gl {

class Camera;
class Framebuffer;
class SceneGraph;
class Viewport;
class Visitor;

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
