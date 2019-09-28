#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "GLFWApplicationEvents.h"


namespace gl {

class SceneView;

/**
 * @brief The CameraController class
 */
class CameraController
{

public:
    enum CameraType {
        None,
        Static,
        ArcBall
    };

public:
    template <typename... Args>
    static Controller* Create(CameraType type, std::weak_ptr<SceneView> sceneView, Args&&... args)
    {
        switch(type)
        {
        case Static:
            return new DefaultController(sceneView);
        case ArcBall:
            return new GLFWApplicationEvents(sceneView, std::forward<Args>(args)...);
        default:
            return nullptr;
        }
    }
};

}   // namespace gl

#endif
