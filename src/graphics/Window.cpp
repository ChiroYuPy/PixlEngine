//
// Created by ChiroYuki on 19/07/2025.
//

#include <iostream>
#include "graphics/Window.h"

Window::~Window() {
    shutdown();
}

bool Window::initialize(const WindowConfig& config) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWmonitor* monitor = config.fullscreen ? glfwGetPrimaryMonitor() : nullptr;
    m_window = glfwCreateWindow(config.width, config.height, config.title.c_str(), monitor, nullptr);

    if (!m_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);

    setVSync(config.vsync);

    m_width = config.width;
    m_height = config.height;

    return true;
}

void Window::shutdown() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

void Window::swapBuffers() {
    if (m_window) {
        glfwSwapBuffers(m_window);
    }
}

void Window::pollEvents() {
    glfwPollEvents();
}

bool Window::shouldClose() const {
    return m_window == nullptr || glfwWindowShouldClose(m_window);
}

void Window::setShouldClose(bool close) {
    if (m_window) {
        glfwSetWindowShouldClose(m_window, close ? GLFW_TRUE : GLFW_FALSE);
    }
}

void Window::setVSync(bool enabled) {
    glfwSwapInterval(enabled ? 1 : 0);
}

void Window::setFullscreen(bool fullscreen) {
    if (!m_window) return;

    if (fullscreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    } else {
        glfwSetWindowMonitor(m_window, nullptr, 100, 100, m_width, m_height, GLFW_DONT_CARE);
    }
}

void Window::resize(const unsigned int &width, const unsigned int &height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

unsigned int Window::getWidth() const { return m_width; }

unsigned int Window::getHeight() const { return m_height; }

float Window::getAspectRatio() const { return (float)m_width / (float)m_height; }
