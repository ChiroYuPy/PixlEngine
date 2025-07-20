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

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

    void move(CameraMovement direction, float velocity);
    void rotate(float xOffset, float yOffset);

    // Position & Orientation
    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3& position);

    glm::vec3 getFront() const;
    glm::vec3 getUp() const;
    glm::vec3 getRight() const;
    void setOrientation(float yaw, float pitch);
    float getYaw() const;
    float getPitch() const;

    // Configuration
    float getFOV() const;
    void setFOV(float fov);

    float getNearPlane() const;
    void setNearPlane(float nearPlane);

    float getFarPlane() const;
    void setFarPlane(float farPlane);

private:
    void updateCameraVectors();

    // Attributs de position et direction
    glm::vec3 m_position;
    glm::vec3 m_front{};
    glm::vec3 m_up{};
    glm::vec3 m_right{};
    glm::vec3 m_worldUp;

    // Angles d'Euler
    float m_yaw;
    float m_pitch;

    // Paramètres de configuration
    float m_fov;
    float m_nearPlane;
    float m_farPlane;
};

#endif //PIXLENGINE_CAMERA_H
