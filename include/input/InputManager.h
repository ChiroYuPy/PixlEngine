//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_INPUTMANAGER_H
#define PIXLENGINE_INPUTMANAGER_H

#include <GLT.h>
#include <functional>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <functional>
#include <unordered_map>
#include <utility>

enum class KeyState {
    Released,
    Pressed,
    Held
};

enum class MouseButton {
    Left = GLFW_MOUSE_BUTTON_LEFT,
    Right = GLFW_MOUSE_BUTTON_RIGHT,
    Middle = GLFW_MOUSE_BUTTON_MIDDLE
};

class InputManager {
public:
    using KeyCallback = std::function<void(int, KeyState)>;
    using MouseCallback = std::function<void(MouseButton, KeyState)>;
    using MouseMoveCallback = std::function<void(double, double)>;
    using ScrollCallback = std::function<void(double, double)>;
    using ResizeCallback = std::function<void(int, int)>;

    InputManager() = default;
    ~InputManager();

    // Supprime la copie pour éviter les problèmes avec les callbacks GLFW
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    bool initialize(GLFWwindow* window);
    void update();
    void shutdown();

    // Clavier
    bool isKeyPressed(int key) const;
    bool isKeyHeld(int key) const;
    bool isKeyReleased(int key) const;

    // Souris
    bool isMouseButtonPressed(MouseButton button) const;
    bool isMouseButtonHeld(MouseButton button) const;
    bool isMouseButtonReleased(MouseButton button) const;

    glm::vec2 getMousePosition() const { return m_mousePos; }
    glm::vec2 getMouseDelta() const { return m_mouseDelta; }
    glm::vec2 getScrollOffset() const { return m_scrollOffset; }

    // Callbacks
    void setKeyCallback(KeyCallback callback) { m_keyCallback = std::move(callback); }
    void setMouseCallback(MouseCallback callback) { m_mouseCallback = std::move(callback); }
    void setMouseMoveCallback(MouseMoveCallback callback) { m_mouseMoveCallback = std::move(callback); }
    void setScrollCallback(ScrollCallback callback) { m_scrollCallback = std::move(callback); }
    void setResizeCallback(ResizeCallback callback) { m_resizeCallback = std::move(callback); }

    // Utilitaires
    void setCursorMode(int mode); // GLFW_CURSOR_NORMAL, GLFW_CURSOR_HIDDEN, GLFW_CURSOR_DISABLED

private:
    static void keyCallbackGLFW(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallbackGLFW(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallbackGLFW(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallbackGLFW(GLFWwindow* window, double xoffset, double yoffset);
    static void framebufferSizeCallbackGLFW(GLFWwindow *window, int width, int height);

    GLFWwindow* m_window = nullptr;
    std::unordered_map<int, KeyState> m_keyStates;
    std::unordered_map<int, KeyState> m_mouseStates;

    glm::vec2 m_mousePos{0.0f};
    glm::vec2 m_lastMousePos{0.0f};
    glm::vec2 m_mouseDelta{0.0f};
    glm::vec2 m_scrollOffset{0.0f};

    bool m_initialized = false;

    KeyCallback m_keyCallback;
    MouseCallback m_mouseCallback;
    MouseMoveCallback m_mouseMoveCallback;
    ScrollCallback m_scrollCallback;
    ResizeCallback m_resizeCallback;
};

#endif //PIXLENGINE_INPUTMANAGER_H
