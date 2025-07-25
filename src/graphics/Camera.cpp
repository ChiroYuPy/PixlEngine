//
// Created by ChiroYuki on 19/07/2025.
//

#include <algorithm>
#include <cmath>
#include "graphics/Camera.h"
#include "core/Application.h"

Camera::Camera()
        : m_position(0.f, 0.f, 0.f),
          m_worldUp(0.f, 1.f, 0.f),
          m_yaw(-90.f),
          m_pitch(0.f),
          m_fov(45.0f),
          m_nearPlane(0.1f),
          m_farPlane(1000.0f)
{
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
    if (m_viewDirty) {
        m_cachedViewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
        m_viewDirty = false;
    }
    return m_cachedViewMatrix;
}

void Camera::updateAspectRatio() {
    float ar = Application::get().getWindow()->getAspectRatio();
    if (aspectRatio != ar) {
        aspectRatio = ar;
        markProjDirty();
    }
}

glm::mat4 Camera::getProjectionMatrix() {
    updateAspectRatio();
    if (m_projDirty) {
        m_cachedProjectionMatrix = glm::perspective(glm::radians(m_fov), aspectRatio, m_nearPlane, m_farPlane);
        m_projDirty = false;
    }
    return m_cachedProjectionMatrix;
}

void Camera::move(CameraMovement direction, float velocity) {
    switch (direction) {
        case CameraMovement::Forward:  m_position += m_front * velocity; break;
        case CameraMovement::Backward: m_position -= m_front * velocity; break;
        case CameraMovement::Left:     m_position -= m_right * velocity; break;
        case CameraMovement::Right:    m_position += m_right * velocity; break;
        case CameraMovement::Up:       m_position += m_up * velocity; break;
        case CameraMovement::Down:     m_position -= m_up * velocity; break;
        default: break;
    }
    markViewDirty();
}

void Camera::rotate(float xOffset, float yOffset) {
    m_yaw += xOffset;
    m_pitch += yOffset;
    m_pitch = std::clamp(m_pitch, MIN_PITCH, MAX_PITCH);

    updateCameraVectors();
    markViewDirty();
}

void Camera::setOrientation(float yaw, float pitch) {
    m_yaw = std::fmod(yaw, MAX_YAW);
    if (m_yaw < 0.f) m_yaw += MAX_YAW;

    m_pitch = std::clamp(pitch, MIN_PITCH, MAX_PITCH);
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = static_cast<float>(cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)));
    front.y = static_cast<float>(sin(glm::radians(m_pitch)));
    front.z = static_cast<float>(sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)));
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}

// ==== Getters / Setters ====

glm::vec3 Camera::getPosition() const { return m_position; }
void Camera::setPosition(const glm::vec3& position) {
    m_position = position;
    markViewDirty();
}

glm::vec3 Camera::getFront() const { return m_front; }
glm::vec3 Camera::getUp() const { return m_up; }
glm::vec3 Camera::getRight() const { return m_right; }

float Camera::getYaw() const { return m_yaw; }
float Camera::getPitch() const { return m_pitch; }

float Camera::getFOV() const { return m_fov; }
void Camera::setFOV(float fov) {
    m_fov = std::clamp(fov, MIN_FOV, MAX_FOV);
    markProjDirty();
}

float Camera::getNearPlane() const { return m_nearPlane; }

float Camera::getFarPlane() const { return m_farPlane; }

void Camera::setNearPlane(float nearPlane) {
    m_nearPlane = std::max(0.01f, nearPlane);
    markProjDirty();
}

void Camera::setFarPlane(float farPlane) {
    m_farPlane = std::max(m_nearPlane + 0.01f, farPlane);
    markProjDirty();
}

void Camera::markViewDirty() {
    m_viewDirty = true;
}

void Camera::markProjDirty() {
    m_projDirty = true;
}