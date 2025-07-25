//
// Created by ChiroYuki on 19/07/2025.
//

#include "graphics/Window.h"
#include "core/Logger.h"

Window::Window(unsigned int width, unsigned int height, const std::string& title)
: m_width(width), m_height(height), m_title(title) {}

Window::~Window() {
    destroyGLFWwindow();
}

bool Window::initialize() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!initGLFWwindow()) return false;

    return true;
}

bool Window::initGLFWwindow() {
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

    if (!m_window) {
        Logger::error() << "Failed to create GLFW window";
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);

    return true;
}

void Window::destroyGLFWwindow() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::swapBuffers() {
    if (m_window) {
        glfwSwapBuffers(m_window);
    }
}

bool Window::shouldClose() const {
    return m_window == nullptr || glfwWindowShouldClose(m_window);
}

void Window::resize(const unsigned int &width, const unsigned int &height) {
    m_width = width;
    m_height = height;
}

unsigned int Window::getWidth() const {
    return m_width;
}

unsigned int Window::getHeight() const {
    return m_height;
}

float Window::getAspectRatio() const {
    return (float)m_width / (float)m_height;
}
