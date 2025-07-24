//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_CHUNK_H
#define PIXLENGINE_CHUNK_H

#include <memory>
#include <GLT.h>
#include "voxelEngine/voxelWorld/voxel/VoxelArray.h"
#include "voxelEngine/voxelWorld/utils/DirectionUtils.h"
#include "graphics/IMesh.h"
#include "ChunkMesh.h"

struct ChunkCoord {
    int x, y, z;

    ChunkCoord(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}

    bool operator==(const ChunkCoord& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const ChunkCoord& other) const {
        return !(*this == other);
    }
};

namespace std {
    template<>
    struct hash<ChunkCoord> {
        size_t operator()(const ChunkCoord& coord) const {
            size_t h1 = hash<int>{}(coord.x);
            size_t h2 = hash<int>{}(coord.y);
            size_t h3 = hash<int>{}(coord.z);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}

class Chunk {
public:
    explicit Chunk(ChunkCoord coord);

    voxel::ID get(int x, int y, int z) const;
    voxel::ID get(const glm::ivec3& pos) const;

    void set(int x, int y, int z, voxel::ID voxel);
    void set(const glm::ivec3& pos, voxel::ID voxel);

    void fill(voxel::ID ID);

    void markDirty();

    glm::ivec3 getPosition() const;

    void buildMesh(const World& world);

    void drawOpaque(Shader& shader) const;
    void drawTransparent(Shader& shader) const;

private:
    ChunkCoord m_position;
    VoxelArray m_storage;

    ChunkMesh m_opaqueMesh;
    ChunkMesh m_transparentMesh;

    bool m_dirty = true;

    static bool isInBounds(int x, int y, int z);
};

#endif //PIXLENGINE_CHUNK_H
