//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_CAMERA_H
#define PIXLENGINE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement {
    Forward,
    Backward,
    Left,
    Right,
    Up,
    Down
};

constexpr float MAX_YAW = 360.f;
constexpr float MIN_PITCH = -89.9f;
constexpr float MAX_PITCH = 89.9f;
constexpr float MIN_FOV = 1.0f;
constexpr float MAX_FOV = 179.9f;

class Camera {
public:
    Camera();

    // Mouvements
    void move(CameraMovement direction, float velocity);
    void rotate(float xOffset, float yOffset);
    void setOrientation(float yaw, float pitch);
    void setPosition(const glm::vec3& position);

    // Projections
    void setFOV(float fov);
    void setNearPlane(float nearPlane);
    void setFarPlane(float farPlane);

    // Matrices
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    // Getters
    glm::vec3 getPosition() const;
    glm::vec3 getFront() const;
    glm::vec3 getUp() const;
    glm::vec3 getRight() const;

    float getYaw() const;
    float getPitch() const;
    float getFOV() const;
    float getNearPlane() const;
    float getFarPlane() const;

private:
    void updateCameraVectors();
    void updateAspectRatio();
    void markViewDirty();
    void markProjDirty();

    glm::vec3 m_position;
    glm::vec3 m_front{}, m_up{}, m_right{};
    glm::vec3 m_worldUp;

    float m_yaw, m_pitch;
    float m_fov;
    float m_nearPlane, m_farPlane;
    float aspectRatio = 1.f;

    glm::mat4 m_cachedViewMatrix;
    glm::mat4 m_cachedProjectionMatrix;

    bool m_viewDirty = true;
    bool m_projDirty = true;
};

#endif //PIXLENGINE_CAMERA_H
