//
// Created by ChiroYuki on 19/07/2025.
//

#include <iostream>
#include "scene/SceneManager.h"

SceneManager::~SceneManager() {
    unloadCurrentScene();
}

bool SceneManager::loadScene(const std::string& name) {
    auto it = m_sceneFactories.find(name);
    if (it == m_sceneFactories.end()) {
        std::cerr << "Scene '" << name << "' not found" << std::endl;
        return false;
    }

    unloadCurrentScene();

    m_currentScene = it->second();
    if (!m_currentScene || !m_currentScene->initialize()) {
        std::cerr << "Failed to initialize scene '" << name << "'" << std::endl;
        m_currentScene.reset();
        return false;
    }

    m_currentSceneName = name;
    m_currentScene->onEnter();

    return true;
}

void SceneManager::unloadCurrentScene() {
    if (m_currentScene) {
        m_currentScene->onExit();
        m_currentScene->shutdown();
        m_currentScene.reset();
        m_currentSceneName.clear();
    }
}

void SceneManager::update(float deltaTime) {
    if (m_currentScene)
        m_currentScene->update(deltaTime);
}

void SceneManager::render() {
    if (m_currentScene)
        m_currentScene->render();
}
