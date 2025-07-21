//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_CHUNKSCENE_H
#define PIXLENGINE_CHUNKSCENE_H

#include "scene/SceneManager.h"
#include "graphics/Camera.h"
#include "graphics/Shader.h"
#include "core/Application.h"
#include "utils/MeshGenerator.h"
#include "voxelEngine/voxelWorld/storage/VoxelArray.h"
#include "CameraController.h"
#include "voxelEngine/voxelWorld/world/VoxelWorld.h"

class ChunkScene : public Scene {
public:
    bool initialize() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;

private:
    std::shared_ptr<Camera> m_camera;
    std::unique_ptr<CameraController> m_cameraController;
    std::unique_ptr<Shader> m_chunkShader;
    std::unique_ptr<VoxelWorld> m_world;

    // Stockage des meshes par chunk
    std::unordered_map<ChunkCoord, std::unique_ptr<Mesh>> m_chunkMeshes;

    // Méthodes pour la gestion des chunks
    void buildAllChunksMesh();
    void buildChunkMesh(const ChunkCoord& chunkCoord, VoxelChunk* chunk);
    void renderAllChunks(const glm::mat4& view, const glm::mat4& projection);

    // Utilitaires pour le mesh building
    bool isFaceExposed(const ChunkCoord& chunkCoord, VoxelChunk* chunk, int x, int y, int z, int face);
    glm::ivec3 getFaceOffset(int face);
};

#endif //PIXLENGINE_CHUNKSCENE_H
