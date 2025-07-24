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
#include "Time.h"

class Application {
public:
    static Application& get();

    bool initialize();
    void run();
    void shutdown();

    // Getters pour les sous-systèmes
    Window* getWindow() const;
    Renderer* getRenderer() const;
    InputManager* getInputManager() const;
    SceneManager* getSceneManager() const;

    bool isRunning() const;
    void setShouldQuit();

    float getElapsedTime() const;
    float getDeltaTime() const;

private:
    Application() = default;
    ~Application() = default;

    void update();
    void render();

    bool initServices();
    bool initGLFW();
    void initDefaultHandlers();

    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<InputManager> m_inputManager;
    std::unique_ptr<SceneManager> m_sceneManager;

    bool m_running = false;
    Time m_time;

    void quitGLFW();
};


#endif //PIXLENGINE_APPLICATION_H
