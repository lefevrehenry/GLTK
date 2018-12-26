#ifndef RENDERED_H
#define RENDERED_H


namespace gl {

class Camera;
class SceneGraph;
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
    Visitor* visitor;

};

}   // namespace gl

#endif
