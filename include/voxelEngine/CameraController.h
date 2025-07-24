//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_CAMERACONTROLLER_H
#define PIXLENGINE_CAMERACONTROLLER_H

#include <memory>
#include "input/InputManager.h"
#include "graphics/Camera.h"

class CameraController {
public:
    CameraController(InputManager* input, std::shared_ptr<Camera> camera);

    void setActive(bool active);
    bool isActive() const;

    void update(float deltaTime);

private:
    InputManager* m_input;
    std::shared_ptr<Camera> m_camera;

    bool m_active = false;
    float m_movementSpeed = 12.0f;
    float m_rotationSensitivity = 0.33f;
};

#endif //PIXLENGINE_CAMERACONTROLLER_H
