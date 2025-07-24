//
// Created by ChiroYuki on 19/07/2025.
//

#include "core/Application.h"
#include "graphics/Window.h"
#include "core/Logger.h"
#include <iostream>

Application& Application::getInstance() {
    static Application instance;
    return instance;
}

bool Application::initialize() {
    if (!initGLFW()) return false;
    if (!initServices()) return false;
    if (!initDefaultHandlers()) return false;

    m_running = true;
    m_lastTime = std::chrono::high_resolution_clock::now();

    return true;
}

bool Application::initGLFW() {
    if (!glfwInit()) {
        Logger::error("Failed to initialize GLFW");
        return false;
    }
    return true;
}

bool Application::initServices() {
    // ------------ [ Window ] ------------ #
    m_window = std::make_unique<Window>(1280, 720, "Pixl Engine");
    if (!m_window->initialize()) {
        Logger::error("Failed to initialize window");
        return false;
    }

    // ------------ [ Renderer ] ------------ #
    m_renderer = std::make_unique<Renderer>();
    if (!m_renderer->initialize()) {
        Logger::error("Failed to initialize renderer");
        return false;
    }

    // ------------ [ InputManager ] ------------ #
    m_inputManager = std::make_unique<InputManager>();
    if (!m_inputManager->initialize(m_window->getGLFWWindow())) {
        Logger::error("Failed to initialize input manager");
        return false;
    }

    // ------------ [ SceneManager ] ------------ #
    m_sceneManager = std::make_unique<SceneManager>();

    return true;
}

bool Application::initDefaultHandlers() {
    m_inputManager->setResizeCallback([this](int width, int height) {
        Logger::info(std::format("Window resized to {}x{}", width, height));
        m_window->resize(width, height);
        m_renderer->setViewport(0, 0, width, height);
    });
    return true;
}

void Application::run() {
    while (m_running && !m_window->shouldClose()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        m_deltaTime = std::chrono::duration<float>(currentTime - m_lastTime).count();
        m_lastTime = currentTime;

        m_window->pollEvents();
        m_inputManager->update();

        update(m_deltaTime);
        render();

        m_window->swapBuffers();
    }
}

void Application::update(float deltaTime) {
    if (m_sceneManager)
        m_sceneManager->update(deltaTime);
}


void Application::render() {
    m_renderer->beginFrame();

    m_renderer->clear();

    if (m_sceneManager) m_sceneManager->render();

    m_renderer->endFrame();
}

void Application::shutdown() {
    if (m_sceneManager) m_sceneManager.reset();
    if (m_inputManager) m_inputManager.reset();
    if (m_renderer) m_renderer.reset();
    if (m_window) m_window.reset();

    glfwTerminate();
    m_running = false;
}

Window *Application::getWindow() const {
    return m_window.get();
}

Renderer *Application::getRenderer() const {
    return m_renderer.get();
}

InputManager *Application::getInputManager() const {
    return m_inputManager.get();
}

SceneManager *Application::getSceneManager() const {
    return m_sceneManager.get();
}

bool Application::isRunning() const {
    return m_running;
}

void Application::quit() {
    m_running = false;
}

float Application::getDeltaTime() const {
    return m_deltaTime;
}