//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_CHUNKRENDERER_H
#define PIXLENGINE_CHUNKRENDERER_H

#include "graphics/Camera.h"

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
};


#endif //PIXLENGINE_CHUNKRENDERER_H
