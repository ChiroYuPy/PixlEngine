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
    union {
        uint32_t data = 0;
        struct {
            uint32_t x       : 5;  // Bits 0-4   (0-31)
            uint32_t y       : 5;  // Bits 5-9   (0-31)
            uint32_t z       : 5;  // Bits 10-14 (0-31)
            uint32_t faceID  : 3;  // Bits 15-17 (0-7)
            uint32_t voxelID : 8;  // Bits 18-25 (0-255)
            uint32_t _unused : 6;  // Bits 26-31
        };
    };

    FaceInstance() = default;

    FaceInstance(uint8_t x, uint8_t y, uint8_t z, uint8_t f, uint8_t v) {
        set(x, y, z, f, v);
    }

    explicit FaceInstance(const glm::ivec3& pos, uint8_t f, uint8_t v) {
        set(pos.x, pos.y, pos.z, f, v);
    }

    void set(uint8_t _x, uint8_t _y, uint8_t _z, uint8_t _faceID, uint8_t _voxelID) {
        // Assurer que les valeurs ne dépassent pas les limites des bits alloués
        x = _x & 0x1F;        // 5 bits : 0-31
        y = _y & 0x1F;        // 5 bits : 0-31
        z = _z & 0x1F;        // 5 bits : 0-31
        faceID = _faceID & 0x07;  // 3 bits : 0-7
        voxelID = _voxelID;   // 8 bits : 0-255
        _unused = 0;
    }
};

class ChunkMesh {
public:
    ChunkMesh();
    ~ChunkMesh();

    void uploadInstances(const std::vector<FaceInstance>& instances);
    void draw() const;

private:
    VertexArray vao;
    Buffer instanceBuffer;
    size_t instanceCount = 0;

    void setupBuffers();
    void setupVertexAttribs();
};

#endif //PIXLENGINE_CHUNKMESH_H
