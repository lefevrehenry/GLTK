#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "GLFWApplicationEvents.h"


namespace gl {

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
    static Interface* Create(CameraType type, Args&&... args)
    {
        switch(type)
        {
        case Static:
            return new DefaultInterface();
        case ArcBall:
            return new GLFWApplicationEvents(std::forward<Args>(args)...);
        default:
            return nullptr;
        }
    }
};

}   // namespace gl

#endif
