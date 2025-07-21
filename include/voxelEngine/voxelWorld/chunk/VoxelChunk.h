//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_VOXELCHUNK_H
#define PIXLENGINE_VOXELCHUNK_H

#include <memory>
#include "voxelEngine/voxelWorld/storage/VoxelArray.h"
#include "voxelEngine/voxelWorld/utils/DirectionUtils.h"

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

class VoxelChunk {
public:
    explicit VoxelChunk(ChunkCoord coord);

    Voxel get(int x, int y, int z) const;
    void set(int x, int y, int z, Voxel voxel);

    void clear();
    void fill(voxel::VoxelID ID);

    void setNeighbor(CubicDirection direction, VoxelChunk* neighbor);
    VoxelChunk* getNeighbor(CubicDirection direction) const;

    void markDirty();

private:
    VoxelArray m_storage;
    std::array<VoxelChunk*, 6> m_neighbors;
    ChunkCoord m_position;
    bool m_dirty = true;

    static bool isInBounds(int x, int y, int z);
};

#endif //PIXLENGINE_VOXELCHUNK_H
