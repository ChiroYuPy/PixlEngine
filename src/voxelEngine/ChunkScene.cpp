//
// Created by ChiroYuki on 19/07/2025.
//

#include <random>
#include "voxelEngine/ChunkScene.h"
#include "voxelEngine/voxelWorld/chunk/VoxelChunk.h"
#include "utils/Logger.h"

bool ChunkScene::initialize() {
    m_camera = std::make_shared<Camera>();
    m_camera->setPosition({64.f, 64.f, 64.f});
    m_camera->setFOV(70.f);
    m_camera->setOrientation(215.f, -45.f);

    auto* input = Application::getInstance().getInputManager();
    m_cameraController = std::make_unique<CameraController>(input, m_camera);

    m_chunkShader = std::make_unique<Shader>();

    m_blockColors = {
            glm::vec3(),                            // 0 = air
            glm::vec3(1.0f, 0.0f, 0.0f),   // 1 = red
            glm::vec3(0.0f, 1.0f, 0.0f),   // 2 = green
            glm::vec3(0.0f, 0.0f, 1.0f),   // 3 = blue
            glm::vec3(1.0f, 0.0f, 1.0f)    // 4 = purple
    };

    if (!m_chunkShader->loadFromFiles("resources/shaders/chunk.vert", "resources/shaders/chunk.frag")) return false;

    // Générer un chunk de test (plein sauf en haut)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distAir(0, 4);  // 0 = air, 1-4 = types de blocs

    const double voxelMemoryUsage = sizeof(Voxel);
    Logger::warn(std::format("voxel memoryUsage: {}", voxelMemoryUsage));

    m_chunk = std::make_unique<DenseVoxelStorage>();

    uint8_t id = 0;
    for (int x = 0; x < IVoxelStorage::SIZE; ++x)
        for (int y = 0; y < IVoxelStorage::SIZE; ++y)
            for (int z = 0; z < IVoxelStorage::SIZE; ++z) {
                m_chunk->set(x, y, z, Voxel{id});
                id = 1 + (id % (m_blockColors.size() - 1));
                // id = (id + 1) % 256;
            }

    const double chunkMemoryUsage = m_chunk->getMemoryUsage();
    Logger::warn(std::format("chunk memoryUsage: {}", chunkMemoryUsage));

    buildChunkMesh();

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
    m_cameraController->update(deltaTime);
}

void ChunkScene::render() {
    auto* renderer = Application::getInstance().getRenderer();
    auto* window = Application::getInstance().getWindow();

    auto model = glm::mat4(1.0f);
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 proj = m_camera->getProjectionMatrix(window->getAspectRatio());

    m_chunkShader->use();
    m_chunkShader->setMat4("u_Model", model);
    m_chunkShader->setMat4("u_View", view);
    m_chunkShader->setMat4("u_Projection", proj);

    renderer->drawMesh(*m_chunkMesh, *m_chunkShader, model);
}

void ChunkScene::shutdown() {
    m_chunkMesh.reset();
    m_chunkShader.reset();
    m_camera.reset();
}

void ChunkScene::buildChunkMesh() {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (int x = 0; x < IVoxelStorage::SIZE; ++x)
        for (int y = 0; y < IVoxelStorage::SIZE; ++y)
            for (int z = 0; z < IVoxelStorage::SIZE; ++z) {
                Voxel voxel = m_chunk->get(x, y, z);
                if (voxel.ID == 0) continue;

                glm::vec3 pos(x, y, z);
                glm::vec3 color = m_blockColors[voxel.ID];

                for (int face = 0; face < 6; ++face) {
                    glm::ivec3 offset = getFaceOffset(face);
                    int nx = x + offset.x;
                    int ny = y + offset.y;
                    int nz = z + offset.z;

                    bool exposed = (nx < 0 || ny < 0 || nz < 0 ||
                                    nx >= IVoxelStorage::SIZE || ny >= IVoxelStorage::SIZE || nz >= IVoxelStorage::SIZE ||
                                    m_chunk->get(nx, ny, nz).ID == VoxelType::AIR);

                    if (exposed)
                        MeshGenerator::addCubeFace(vertices, indices, pos, face, color);
                }
            }

    m_chunkMesh = std::make_unique<Mesh>();
    m_chunkMesh->setVertices(vertices);
    m_chunkMesh->setIndices(indices);
    m_chunkMesh->upload();
}

glm::ivec3 ChunkScene::getFaceOffset(int face) {
    switch (face) {
        case 0: return {0, 0, 1};  // front
        case 1: return {0, 0, -1}; // back
        case 2: return {-1, 0, 0}; // left
        case 3: return {1, 0, 0};  // right
        case 4: return {0, 1, 0};  // top
        case 5: return {0, -1, 0}; // bottom
        default: return {0, 0, 0};
    }
}
