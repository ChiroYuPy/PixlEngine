//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_WORLDRENDERER_H
#define PIXLENGINE_WORLDRENDERER_H

#include "graphics/Camera.h"
#include "voxelEngine/voxelWorld/world/TextureColorPalette.h"

class World;
class Shader;

class WorldRenderer {
public:
    WorldRenderer(World& world, Camera& camera, Shader& shader);
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

    void renderTransparentPass();
};


#endif //PIXLENGINE_WORLDRENDERER_H
