//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_CHUNKRENDERER_H
#define PIXLENGINE_CHUNKRENDERER_H

class World;
class Shader;

class ChunkRenderer {
public:
    ChunkRenderer(World& world);
    void buildAll();
    void renderAll(Shader& shader);

private:
    World& m_world;
};


#endif //PIXLENGINE_CHUNKRENDERER_H
