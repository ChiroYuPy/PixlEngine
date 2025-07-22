//
// Created by ChiroYuki on 19/07/2025.
//

#include <random>
#include <iostream>
#include "voxelEngine/ChunkScene.h"
#include "voxelEngine/voxelWorld/chunk/Chunk.h"
#include "utils/Logger.h"

bool ChunkScene::initialize() {
    m_camera = std::make_shared<Camera>();
    m_camera->setPosition({64.f, 64.f, 64.f});
    m_camera->setFOV(70.f);
    m_camera->setOrientation(215.f, -45.f);

    auto* input = Application::getInstance().getInputManager();
    m_cameraController = std::make_unique<CameraController>(input, m_camera);

    m_chunkShader = std::make_unique<Shader>();

    if (!m_chunkShader->loadFromFiles("resources/shaders/chunk.vert", "resources/shaders/chunk.frag")) {
        std::cerr << "Failed to load chunk shaders" << std::endl;
        return false;
    }

    m_world = std::make_unique<World>();

    try {
        constexpr unsigned int SIZE = 12;
        m_world->generateArea({-(SIZE-1), -1, -(SIZE-1)}, {SIZE, 1, SIZE});
        buildAllChunksMesh();
    } catch (const std::exception& e) {
        std::cerr << "Error during world generation: " << e.what() << std::endl;
        return false;
    }

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

    return true;
}

void ChunkScene::update(float deltaTime) {
    if (m_cameraController)
        m_cameraController->update(deltaTime);
}

void ChunkScene::render() {
    auto* renderer = Application::getInstance().getRenderer();
    auto* window = Application::getInstance().getWindow();

    if (!renderer || !window || !m_camera || !m_chunkShader) {
        Logger::warn("render aborted, missing some components");
        return;
    }

    float aspectRatio = window->getAspectRatio();

    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 proj = m_camera->getProjectionMatrix(aspectRatio);

    m_chunkShader->use();
    m_chunkShader->setMat4("u_View", view);
    m_chunkShader->setMat4("u_Projection", proj);

    renderAllChunks();
}

void ChunkScene::shutdown() {
    m_chunkShader.reset();
    m_camera.reset();
    m_world.reset();
    m_cameraController.reset();
}

void ChunkScene::buildAllChunksMesh() {
    if (!m_world) return;
    m_world->forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk) chunk->buildMesh(*m_world);
    });
}

void ChunkScene::renderAllChunks() {
    m_world->forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk) {
            const ChunkMesh* mesh = chunk->getMesh();
            if (mesh) mesh->render(*m_chunkShader);
        }
    });
}