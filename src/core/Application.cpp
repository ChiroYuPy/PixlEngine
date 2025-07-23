//
// Created by ChiroYuki on 19/07/2025.
//

#include "core/Application.h"
#include "graphics/Window.h"
#include <iostream>

Application& Application::getInstance() {
    static Application instance;
    return instance;
}

bool Application::initialize() {
    // Initialiser GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // Créer et initialiser la fenêtre
    m_window = std::make_unique<Window>();
    WindowConfig config;
    config.title = "Pixl Engine";
    config.width = 1280;
    config.height = 720;

    if (!m_window->initialize(config)) {
        std::cerr << "Failed to initialize window" << std::endl;
        return false;
    }

    // Créer et initialiser le renderer
    m_renderer = std::make_unique<Renderer>();
    if (!m_renderer->initialize()) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return false;
    }

    // Créer et initialiser l'input manager
    m_inputManager = std::make_unique<InputManager>();
    if (!m_inputManager->initialize(m_window->getGLFWWindow())) {
        std::cerr << "Failed to initialize input manager" << std::endl;
        return false;
    }

    // Créer le scene manager
    m_sceneManager = std::make_unique<SceneManager>();

    // Setup callbacks
    m_window->setResizeCallback([this](int width, int height) {
        m_renderer->setViewport(0, 0, width, height);
    });

    m_window->setVSync(false);

    m_running = true;
    m_lastTime = std::chrono::high_resolution_clock::now();

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
    if (m_sceneManager) {
        m_sceneManager->update(deltaTime);
    }
}


void Application::render() {
    m_renderer->beginFrame();
    m_renderer->clear();

    if (m_sceneManager) {
        m_sceneManager->render();
    }

    m_renderer->endFrame();
}

void Application::shutdown() {
    if (m_sceneManager) {
        m_sceneManager.reset();
    }
    if (m_inputManager) {
        m_inputManager.reset();
    }
    if (m_renderer) {
        m_renderer->shutdown();
        m_renderer.reset();
    }
    if (m_window) {
        m_window->shutdown();
        m_window.reset();
    }

    glfwTerminate();
    m_running = false;
}