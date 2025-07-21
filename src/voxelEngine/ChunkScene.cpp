//
// Created by ChiroYuki on 19/07/2025.
//

#include <random>
#include <iostream>
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

    if (!m_chunkShader->loadFromFiles("resources/shaders/chunk.vert", "resources/shaders/chunk.frag")) return false;

    // Initialisation du ChunkStorage
    m_world = std::make_unique<VoxelWorld>();

    // Création de quelques chunks pour le test
    VoxelChunk* c1 = m_world->getOrCreateChunk(0, 0, 0);
    VoxelChunk* c2 = m_world->getOrCreateChunk(1, 0, 0);
    VoxelChunk* c3 = m_world->getOrCreateChunk(0, 0, 1);

    c1->fill(voxel::GRASS);

    c1->set(0, 0, 0, Voxel{voxel::STONE});

    std::cout << "ID: " << voxel::getVoxelDisplayName(c1->get(0, 0, 0).ID) << std::endl;

    // Construire le mesh pour tous les chunks chargés
    buildAllChunksMesh();

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

    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 proj = m_camera->getProjectionMatrix(window->getAspectRatio());

    m_chunkShader->use();
    m_chunkShader->setMat4("u_View", view);
    m_chunkShader->setMat4("u_Projection", proj);

    // Rendu de tous les chunks
    renderAllChunks(view, proj);
}

void ChunkScene::shutdown() {
    m_chunkMeshes.clear();
    m_chunkShader.reset();
    m_camera.reset();
    m_world.reset();
}

void ChunkScene::buildAllChunksMesh() {
    m_chunkMeshes.clear();

    // Construire le mesh pour chaque chunk chargé
    m_world->forEachChunk([this](const ChunkCoord& coord, VoxelChunk* chunk) {
        buildChunkMesh(coord, chunk);
    });
}

void ChunkScene::buildChunkMesh(const ChunkCoord& chunkCoord, VoxelChunk* chunk) {
    if (!chunk) return;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Offset de position du chunk dans le monde
    glm::vec3 chunkOffset(
            chunkCoord.x * VoxelArray::SIZE,
            chunkCoord.y * VoxelArray::SIZE,
            chunkCoord.z * VoxelArray::SIZE
    );

    for (int x = 0; x < VoxelArray::SIZE; ++x) {
        for (int y = 0; y < VoxelArray::SIZE; ++y) {
            for (int z = 0; z < VoxelArray::SIZE; ++z) {
                Voxel voxel = chunk->get(x, y, z);
                if (voxel.ID == 0) continue;

                glm::vec3 pos = chunkOffset + glm::vec3(x, y, z);
                uint32_t hexColor = voxel::getVoxelColorRGBA(voxel.ID);

                float r = ((hexColor >> 16) & 0xFF) / 255.0f;
                float g = ((hexColor >> 8)  & 0xFF) / 255.0f;
                float b = ((hexColor >> 0)  & 0xFF) / 255.0f;
                glm::vec3 color = glm::vec3(r, g, b);

                for (int face = 0; face < 6; ++face) {
                    if (isFaceExposed(chunkCoord, chunk, x, y, z, face)) {
                        MeshGenerator::addCubeFace(vertices, indices, pos, face, color);
                    }
                }
            }
        }
    }

    if (!vertices.empty()) {
        auto mesh = std::make_unique<Mesh>();
        mesh->setVertices(vertices);
        mesh->setIndices(indices);
        mesh->upload();
        m_chunkMeshes[chunkCoord] = std::move(mesh);
    }
}

bool ChunkScene::isFaceExposed(const ChunkCoord& chunkCoord, VoxelChunk* chunk, int x, int y, int z, int face) {
    glm::ivec3 offset = getFaceOffset(face);
    int nx = x + offset.x;
    int ny = y + offset.y;
    int nz = z + offset.z;

    // Vérifier si le voxel voisin est dans le même chunk
    if (nx >= 0 && ny >= 0 && nz >= 0 &&
        nx < VoxelArray::SIZE && ny < VoxelArray::SIZE && nz < VoxelArray::SIZE) {
        // Le voisin est dans le même chunk
        return chunk->get(nx, ny, nz).ID == voxel::AIR;
    }

    // Le voisin est dans un autre chunk, utiliser les coordonnées globales
    int worldX = chunkCoord.x * VoxelArray::SIZE + nx;
    int worldY = chunkCoord.y * VoxelArray::SIZE + ny;
    int worldZ = chunkCoord.z * VoxelArray::SIZE + nz;

    Voxel neighborVoxel = m_world->getVoxel(worldX, worldY, worldZ);
    return neighborVoxel.ID == voxel::AIR;
}

void ChunkScene::renderAllChunks(const glm::mat4& view, const glm::mat4& projection) {
    auto* renderer = Application::getInstance().getRenderer();

    for (const auto& pair : m_chunkMeshes) {
        const ChunkCoord& coord = pair.first;
        const std::unique_ptr<Mesh>& mesh = pair.second;

        // Matrice de modèle pour positionner le chunk dans le monde
        auto model = glm::mat4(1.0f);
        // Note: La position est déjà intégrée dans les vertices du mesh

        m_chunkShader->setMat4("u_Model", model);
        renderer->drawMesh(*mesh, *m_chunkShader, model);
    }
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