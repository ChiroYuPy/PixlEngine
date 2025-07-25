//
// Created by ChiroYuki on 19/07/2025.
//

#include "input/InputManager.h"
#include "core/Logger.h"
#include <format>

InputManager::~InputManager() {
    shutdown();
}

bool InputManager::initialize(GLFWwindow* window) {
    if (m_initialized) {
        Logger::warn() << "InputManager already initialized";
        return true;
    }

    if (!window) {
        Logger::error() << "InputManager::initialize - window is null";
        return false;
    }

    m_window = window;

    // Configuration des callbacks GLFW
    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(window, keyCallbackGLFW);
    glfwSetMouseButtonCallback(window, mouseButtonCallbackGLFW);
    glfwSetCursorPosCallback(window, cursorPosCallbackGLFW);
    glfwSetScrollCallback(window, scrollCallbackGLFW);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallbackGLFW);

    // Initialisation de la position de la souris
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    m_mousePos = m_lastMousePos = glm::vec2(static_cast<float>(x), static_cast<float>(y));

    Logger::info() << std::format("First frame mouse position: ({:.2f}, {:.2f})", m_mousePos.x, m_mousePos.y);

    m_initialized = true;
    return true;
}

void InputManager::shutdown() {
    if (!m_initialized) return;

    if (m_window) {
        glfwSetKeyCallback(m_window, nullptr);
        glfwSetMouseButtonCallback(m_window, nullptr);
        glfwSetCursorPosCallback(m_window, nullptr);
        glfwSetScrollCallback(m_window, nullptr);
        glfwSetFramebufferSizeCallback(m_window, nullptr);
    }

    m_keyStates.clear();
    m_mouseStates.clear();

    m_window = nullptr;
    m_initialized = false;

    Logger::info() << "InputManager destroyGLFWwindow complete";
}

void InputManager::update() {
    if (!m_initialized) return;

    // Mise à jour des états du clavier
    for (auto it = m_keyStates.begin(); it != m_keyStates.end();) {
        if (it->second == KeyState::Pressed) {
            it->second = KeyState::Held;
            ++it;
        } else if (it->second == KeyState::Released) {
            it = m_keyStates.erase(it);
        } else {
            ++it;
        }
    }

    // Mise à jour des états de la souris
    for (auto it = m_mouseStates.begin(); it != m_mouseStates.end();) {
        if (it->second == KeyState::Pressed) {
            it->second = KeyState::Held;
            ++it;
        } else if (it->second == KeyState::Released) {
            it = m_mouseStates.erase(it);
        } else {
            ++it;
        }
    }

    // Mise à jour du mouvement de la souris
    m_mouseDelta = m_mousePos - m_lastMousePos;
    m_lastMousePos = m_mousePos;

    // Reset du scroll offset après chaque frame
    m_scrollOffset = glm::vec2(0.0f);
}

// Méthodes du clavier
bool InputManager::isKeyPressed(int key) const {
    auto it = m_keyStates.find(key);
    return it != m_keyStates.end() && it->second == KeyState::Pressed;
}

bool InputManager::isKeyHeld(int key) const {
    auto it = m_keyStates.find(key);
    return it != m_keyStates.end() && (it->second == KeyState::Held || it->second == KeyState::Pressed);
}

bool InputManager::isKeyReleased(int key) const {
    auto it = m_keyStates.find(key);
    return it != m_keyStates.end() && it->second == KeyState::Released;
}

// Méthodes de la souris
bool InputManager::isMouseButtonPressed(MouseButton button) const {
    auto it = m_mouseStates.find(static_cast<int>(button));
    return it != m_mouseStates.end() && it->second == KeyState::Pressed;
}

bool InputManager::isMouseButtonHeld(MouseButton button) const {
    auto it = m_mouseStates.find(static_cast<int>(button));
    return it != m_mouseStates.end() && (it->second == KeyState::Held || it->second == KeyState::Pressed);
}

bool InputManager::isMouseButtonReleased(MouseButton button) const {
    auto it = m_mouseStates.find(static_cast<int>(button));
    return it != m_mouseStates.end() && it->second == KeyState::Released;
}

// Mode curseur
void InputManager::setCursorMode(int mode) {
    if (m_window && m_initialized) {
        glfwSetInputMode(m_window, GLFW_CURSOR, mode);
    }
}

// Callbacks GLFW statiques
void InputManager::keyCallbackGLFW(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (!input || !input->m_initialized) return;

    KeyState state;
    if (action == GLFW_PRESS) {
        state = KeyState::Pressed;
    } else if (action == GLFW_RELEASE) {
        state = KeyState::Released;
    } else {
        return; // Ignore GLFW_REPEAT pour notre système d'états
    }

    input->m_keyStates[key] = state;

    // Appel du callback utilisateur si défini
    if (input->m_keyCallback) {
        input->m_keyCallback(key, state);
    }
}

void InputManager::mouseButtonCallbackGLFW(GLFWwindow* window, int button, int action, int mods) {
    auto* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (!input || !input->m_initialized) return;

    KeyState state;
    if (action == GLFW_PRESS)
        state = KeyState::Pressed;
    else if (action == GLFW_RELEASE)
        state = KeyState::Released;
    else return;

    input->m_mouseStates[button] = state;

    // Appel du callback utilisateur si défini
    if (input->m_mouseCallback) {
        input->m_mouseCallback(static_cast<MouseButton>(button), state);
    }
}

void InputManager::cursorPosCallbackGLFW(GLFWwindow* window, double xpos, double ypos) {
    auto* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (!input || !input->m_initialized) return;

    input->m_mousePos = glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));

    // Appel du callback utilisateur si défini
    if (input->m_mouseMoveCallback) {
        input->m_mouseMoveCallback(xpos, ypos);
    }
}

void InputManager::scrollCallbackGLFW(GLFWwindow* window, double xoffset, double yoffset) {
    auto* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (!input || !input->m_initialized) return;

    input->m_scrollOffset = glm::vec2(static_cast<float>(xoffset), static_cast<float>(yoffset));

    // Appel du callback utilisateur si défini
    if (input->m_scrollCallback) {
        input->m_scrollCallback(xoffset, yoffset);
    }
}

void InputManager::framebufferSizeCallbackGLFW(GLFWwindow* window, int width, int height) {
    auto* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (!input || !input->m_initialized) return;

    if (input->m_resizeCallback) {
        input->m_resizeCallback(width, height);
    }
}