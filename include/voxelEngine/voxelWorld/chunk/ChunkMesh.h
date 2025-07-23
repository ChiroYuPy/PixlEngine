//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_CHUNKMESH_H
#define PIXLENGINE_CHUNKMESH_H

#include "GLT.h"
#include <memory>
#include "graphics/Shader.h"
#include "graphics/Mesh.h"
#include "graphics/objects/VertexArray.h"
#include "graphics/objects/Buffer.h"

class World;
class Chunk;

struct FaceInstance {
    glm::ivec3 position;
    glm::uint8_t faceID;
    glm::uint8_t voxelID;
};

class ChunkMesh {
public:
    ChunkMesh();
    ~ChunkMesh();

    void uploadInstances(const std::vector<FaceInstance>& instances);
    void draw() const;

private:
    VertexArray vao;
    Buffer vertexBuffer;
    Buffer instanceBuffer;
    size_t instanceCount = 0;

    void setupBuffers();
    void setupVertexAttribs();
};

#endif //PIXLENGINE_CHUNKMESH_H
