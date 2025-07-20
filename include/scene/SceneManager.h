//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_SCENEMANAGER_H
#define PIXLENGINE_SCENEMANAGER_H

#include <GLT.h>
#include <unordered_map>
#include <memory>
#include <functional>

class Scene {
public:
    virtual ~Scene() = default;

    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;

    virtual void onEnter() {}
    virtual void onExit() {}

protected:
    bool m_initialized = false;
};

class SceneManager {
public:
    SceneManager() = default;
    ~SceneManager();

    template<typename T>
    void registerScene(const std::string& name) {
        m_sceneFactories[name] = []() { return std::make_unique<T>(); };
    }

    bool loadScene(const std::string& name);
    void unloadCurrentScene();

    void update(float deltaTime);
    void render();

    Scene* getCurrentScene() const { return m_currentScene.get(); }

private:
    using SceneFactory = std::function<std::unique_ptr<Scene>()>;

    std::unordered_map<std::string, SceneFactory> m_sceneFactories;
    std::unique_ptr<Scene> m_currentScene;
    std::string m_currentSceneName;
};

#endif //PIXLENGINE_SCENEMANAGER_H
