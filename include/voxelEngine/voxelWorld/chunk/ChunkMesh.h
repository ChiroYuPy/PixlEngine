//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_CHUNKMESH_H
#define PIXLENGINE_CHUNKMESH_H

#include "GLT.h"
#include <memory>
#include "graphics/Shader.h"
#include "graphics/Mesh.h"

class World;
class Chunk;

class ChunkMesh {
public:
    explicit ChunkMesh(const glm::ivec3& coord);

    void build(const Chunk& chunk, const World& world);
    void render(Shader& shader) const;

    bool isValid() const;

private:
    glm::ivec3 m_coord;
    std::unique_ptr<Mesh<VertexPosColor>> m_mesh;
};

#endif //PIXLENGINE_CHUNKMESH_H
