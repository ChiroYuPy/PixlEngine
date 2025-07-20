//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_APPLICATION_H
#define PIXLENGINE_APPLICATION_H

#include <memory>
#include <chrono>
#include "graphics/Window.h"
#include "graphics/Renderer.h"
#include "input/InputManager.h"
#include "scene/SceneManager.h"

class Application {
public:
    static Application& getInstance();

    bool initialize();
    void run();
    void shutdown();

    // Getters pour les sous-systèmes
    Window* getWindow() const { return m_window.get(); }
    Renderer* getRenderer() const { return m_renderer.get(); }
    InputManager* getInputManager() const { return m_inputManager.get(); }
    SceneManager* getSceneManager() const { return m_sceneManager.get(); }

    bool isRunning() const { return m_running; }
    void quit() { m_running = false; }

    float getDeltaTime() const { return m_deltaTime; }

private:
    Application() = default;
    ~Application() = default;

    void update(float deltaTime);
    void render();

    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<InputManager> m_inputManager;
    std::unique_ptr<SceneManager> m_sceneManager;

    bool m_running = false;
    float m_deltaTime = 0.0f;
    std::chrono::high_resolution_clock::time_point m_lastTime;
};


#endif //PIXLENGINE_APPLICATION_H
