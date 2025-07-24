//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/CameraController.h"

CameraController::CameraController(InputManager* input, std::shared_ptr<Camera> camera)
        : m_input(std::move(input)), m_camera(std::move(camera)) {}

void CameraController::setActive(bool active) {
    m_active = active;
    m_input->setCursorMode(active ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

bool CameraController::isActive() const {
    return m_active;
}

void CameraController::update(float deltaTime) {
    if (!m_active) return;

    float speedMultiplier = 1.0f;
    if (m_input->isKeyHeld(GLFW_KEY_LEFT_CONTROL))
        speedMultiplier = 8.0f;

    float velocity = m_movementSpeed * speedMultiplier * deltaTime;

    if (m_input->isKeyHeld(GLFW_KEY_W)) m_camera->move(CameraMovement::Forward, velocity);
    if (m_input->isKeyHeld(GLFW_KEY_S)) m_camera->move(CameraMovement::Backward, velocity);
    if (m_input->isKeyHeld(GLFW_KEY_A)) m_camera->move(CameraMovement::Left, velocity);
    if (m_input->isKeyHeld(GLFW_KEY_D)) m_camera->move(CameraMovement::Right, velocity);
    if (m_input->isKeyHeld(GLFW_KEY_SPACE)) m_camera->move(CameraMovement::Up, velocity);
    if (m_input->isKeyHeld(GLFW_KEY_LEFT_SHIFT)) m_camera->move(CameraMovement::Down, velocity);

    glm::vec2 delta = m_input->getMouseDelta();
    glm::vec2 offset = delta * m_rotationSensitivity;
    if (glm::length(offset) > 0.001f)
        m_camera->rotate(offset.x, -offset.y);
}