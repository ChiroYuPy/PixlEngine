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
#include "voxelEngine/voxelWorld/voxel/VoxelArray.h"
#include "CameraController.h"
#include "voxelEngine/voxelWorld/world/World.h"

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
    std::unique_ptr<World> m_world;

    // Méthodes pour la gestion des chunks
    void buildAllChunksMesh();
    void renderAllChunks();
};

#endif //PIXLENGINE_CHUNKSCENE_H
