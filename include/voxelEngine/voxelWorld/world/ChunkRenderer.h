//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_CHUNKRENDERER_H
#define PIXLENGINE_CHUNKRENDERER_H

#include "graphics/Camera.h"
#include "voxelEngine/voxelWorld/world/TextureColorPalette.h"

class World;
class Shader;

class ChunkRenderer {
public:
    ChunkRenderer(World& world, Camera& camera, Shader& shader);
    void buildAll();
    void renderAll();

private:
    World& m_world;
    Camera& m_camera;
    Shader& m_shader;

    TextureColorPalette m_textureColorpalette;

    glm::mat4 m_viewProjection;

    void setupRenderStates();

    void setupMatrices();

    void bindCommonResources();

    void renderOpaquePass();

    void renderEmissivePass();

    void renderTransparentPass();
};


#endif //PIXLENGINE_CHUNKRENDERER_H
