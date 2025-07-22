//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_CHUNKRENDERER_H
#define PIXLENGINE_CHUNKRENDERER_H

class World;
class Shader;

class ChunkRenderer {
public:
    ChunkRenderer(World& world, Shader& shader);
    void buildAll();
    void renderAll();

private:
    World& m_world;
    Shader& m_shader;
};


#endif //PIXLENGINE_CHUNKRENDERER_H
