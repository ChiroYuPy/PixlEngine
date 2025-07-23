//
// Created by ChiroYuki on 19/07/2025.
//

#include <random>
#include <iostream>
#include "voxelEngine/ChunkScene.h"
#include "voxelEngine/voxelWorld/chunk/Chunk.h"
#include "utils/Logger.h"

constexpr unsigned int RENDER_DISTANCE = 8;
constexpr unsigned int RENDER_HEIGHT = 1;

bool ChunkScene::initialize() {
    setupCamera();
    setupShader();
    setupWorld();
    setupBlockPlacer();
    setupInput();

    return m_shader && m_world && m_cameraController && m_blockPlacer;
}

void ChunkScene::setupCamera() {
    m_camera = std::make_shared<Camera>();
    m_camera->setPosition(World::toWorldPos({- RENDER_DISTANCE - 1, RENDER_HEIGHT, - RENDER_DISTANCE - 1}));
    m_camera->setFOV(70.f);
    m_camera->setOrientation(45.f, 0.f);

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
    m_chunkRenderer = std::make_unique<ChunkRenderer>(*m_world, *m_camera, *m_shader);

    m_world->generateArea({-RENDER_DISTANCE+1, -RENDER_HEIGHT, -RENDER_DISTANCE+1}, {RENDER_DISTANCE, RENDER_HEIGHT, RENDER_DISTANCE});
    m_chunkRenderer->buildAll();
}

void ChunkScene::setupBlockPlacer() {
    m_blockPlacer = std::make_unique<WorldInteractor>(*m_world, *m_chunkRenderer);
    m_blockPlacer->setMaxReach(64.0f);
    m_blockPlacer->setSelectedBlockType(1);
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

        // Sélection du type de bloc avec les touches numériques
        if (state == KeyState::Pressed) {
            if (key == GLFW_KEY_Z) {
                static int toggle = true;
                Renderer* renderer = Application::getInstance().getRenderer();
                renderer->setWireframeMode(toggle);
                toggle = !toggle;
            }
            else if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9) {
                int blockType = key - GLFW_KEY_0;
                m_blockPlacer->setSelectedBlockType(blockType);
                Logger::info(std::format("Selected block type: {}", blockType));
            }
        }
    });

    input->setMouseCallback([this](MouseButton button, KeyState state) {
        if (button == MouseButton::Left && state == KeyState::Pressed) {
            if (m_cameraController->isActive()) {
                // Casser un bloc
                glm::vec3 cameraPos = m_camera->getPosition();
                glm::vec3 cameraDir = m_camera->getFront();

                if (m_blockPlacer->breakBlock(cameraPos, cameraDir)) {
                    Logger::info("Block broken!");
                } else {
                    Logger::info("No block to break");
                }
            } else {
                m_cameraController->setActive(true);
            }
        }

        if (button == MouseButton::Right && state == KeyState::Pressed) {
            if (m_cameraController->isActive()) {
                // Placer un bloc
                glm::vec3 cameraPos = m_camera->getPosition();
                glm::vec3 cameraDir = m_camera->getFront();

                if (m_blockPlacer->placeBlock(cameraPos, cameraDir)) {
                    Logger::info("Block placed!");
                } else {
                    Logger::info("Cannot place block here");
                }
            }
        }
    });
}

void ChunkScene::update(float deltaTime) {
    if (m_cameraController)
        m_cameraController->update(deltaTime);

    // Optionnel: debug du bloc visé
    if (m_cameraController->isActive() && m_blockPlacer) {
        glm::vec3 cameraPos = m_camera->getPosition();
        glm::vec3 cameraDir = m_camera->getFront();

        auto targetedBlock = m_blockPlacer->getTargetedBlock(cameraPos, cameraDir);
        if (targetedBlock) {
            // Ici vous pourriez afficher un outline du bloc visé
            // ou stocker l'info pour le rendu
            m_targetedBlockPos = targetedBlock->blockPos;
            m_hasTargetedBlock = true;
        } else {
            m_hasTargetedBlock = false;
        }
    }
}

void ChunkScene::render() {
    auto* renderer = Application::getInstance().getRenderer();
    auto* window = Application::getInstance().getWindow();

    if (!renderer || !window || !m_camera || !m_shader) {
        Logger::warn("render aborted, missing some components");
        return;
    }

    m_chunkRenderer->renderAll();
}

void ChunkScene::shutdown() {
    m_shader.reset();
    m_camera.reset();
    m_world.reset();
    m_cameraController.reset();
    m_blockPlacer.reset();
}