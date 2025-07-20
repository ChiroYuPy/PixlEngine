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
#include "voxelEngine/voxelWorld/storage/DenseVoxelStorage.h"
#include "CameraController.h"

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
    std::unique_ptr<Mesh> m_chunkMesh;

    std::array<glm::vec3, 5> m_blockColors;

    std::unique_ptr<IVoxelStorage> m_chunk;

    void buildChunkMesh();

    static glm::ivec3 getFaceOffset(int face);
};


#endif //PIXLENGINE_CHUNKSCENE_H
