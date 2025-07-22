//
// Created by ChiroYuki on 19/07/2025.
//

#include <random>
#include <iostream>
#include "voxelEngine/ChunkScene.h"
#include "voxelEngine/voxelWorld/chunk/Chunk.h"
#include "utils/Logger.h"

bool ChunkScene::initialize() {
    setupCamera();
    setupShader();
    setupWorld();
    setupInput();

    return m_shader && m_world && m_cameraController;
}

void ChunkScene::setupCamera() {
    m_camera = std::make_shared<Camera>();
    m_camera->setPosition({64.f, 64.f, 64.f});
    m_camera->setFOV(70.f);
    m_camera->setOrientation(215.f, -45.f);

    auto* input = Application::getInstance().getInputManager();
    m_cameraController = std::make_unique<CameraController>(input, m_camera);
}

void ChunkScene::setupShader() {
    m_shader = std::make_unique<Shader>();
    if (!m_shader->loadFromFiles("resources/shaders/chunk.vert", "resources/shaders/chunk.frag")) {
        std::cerr << "Failed to load chunk shaders" << std::endl;
        throw std::runtime_error("Shader load failed");
    }
}

void ChunkScene::setupWorld() {
    m_world = std::make_unique<World>();
    m_chunkRenderer = std::make_unique<ChunkRenderer>(*m_world, *m_shader);

    constexpr unsigned int SIZE = 12;
    m_world->generateArea({-(SIZE - 1), -1, -(SIZE - 1)}, {SIZE, 1, SIZE});
    m_chunkRenderer->buildAll();
}

void ChunkScene::setupInput() {
    auto* input = Application::getInstance().getInputManager();

    input->setKeyCallback([this](int key, KeyState state) {
        if (key == GLFW_KEY_ESCAPE && state == KeyState::Pressed) {
            if (m_cameraController->isActive()) {
                m_cameraController->setActive(false);
            } else {
                Application::getInstance().quit();
            }
        }
    });

    input->setMouseCallback([this](MouseButton button, KeyState state) {
        if (button == MouseButton::Left && state == KeyState::Pressed) {
            m_cameraController->setActive(true);
        }
    });
}

void ChunkScene::update(float deltaTime) {
    if (m_cameraController)
        m_cameraController->update(deltaTime);
}

void ChunkScene::render() {
    auto* renderer = Application::getInstance().getRenderer();
    auto* window = Application::getInstance().getWindow();

    if (!renderer || !window || !m_camera || !m_shader) {
        Logger::warn("render aborted, missing some components");
        return;
    }

    float aspectRatio = window->getAspectRatio();

    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 proj = m_camera->getProjectionMatrix(aspectRatio);

    m_shader->use();
    m_shader->setMat4("u_View", view);
    m_shader->setMat4("u_Projection", proj);

    m_chunkRenderer->renderAll();
}

void ChunkScene::shutdown() {
    m_shader.reset();
    m_camera.reset();
    m_world.reset();
    m_cameraController.reset();
}