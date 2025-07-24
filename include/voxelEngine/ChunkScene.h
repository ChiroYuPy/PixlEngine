//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_CHUNKSCENE_H
#define PIXLENGINE_CHUNKSCENE_H

#include "graphics/Camera.h"
#include "graphics/Shader.h"
#include "core/Application.h"
#include "CameraController.h"
#include "scene/SceneManager.h"
#include "voxelEngine/voxelWorld/world/World.h"
#include "voxelEngine/voxelWorld/voxel/VoxelArray.h"
#include "voxelEngine/voxelWorld/world/WorldInteractor.h"
#include "voxelEngine/voxelWorld/world/WorldRenderer.h"

class ChunkScene : public Scene {
public:
    bool initialize() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;

private:
    void setupCamera();
    void setupShader();
    void setupWorld();
    void setupBlockPlacer();
    void setupInput();

    std::shared_ptr<Camera> m_camera;
    std::unique_ptr<CameraController> m_cameraController;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<World> m_world;
    std::unique_ptr<WorldRenderer> m_chunkRenderer;
    std::unique_ptr<WorldInteractor> m_blockPlacer;

    glm::ivec3 m_targetedBlockPos;
    bool m_hasTargetedBlock = false;

    float m_fpsTimer = 0.0f;
    int m_frameCount = 0;
};

#endif //PIXLENGINE_CHUNKSCENE_H
