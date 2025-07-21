//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_VOXELWORLD_H
#define PIXLENGINE_VOXELWORLD_H

#include <GLT.h>
#include <memory>
#include <unordered_map>
#include <functional>
#include "voxelEngine/voxelWorld/voxel/Voxel.h"
#include "voxelEngine/voxelWorld/chunk/VoxelChunk.h"

class VoxelWorld {
public:
    VoxelWorld();
    ~VoxelWorld() = default;

    Voxel getVoxel(int worldX, int worldY, int worldZ) const;
    void setVoxel(int worldX, int worldY, int worldZ, Voxel voxel);
    void setVoxel(int worldX, int worldY, int worldZ, voxel::VoxelID type);

    Voxel getVoxel(const glm::ivec3& worldPos) const;
    void setVoxel(const glm::ivec3& worldPos, Voxel voxel);
    void setVoxel(const glm::ivec3& worldPos, voxel::VoxelID type);

    VoxelChunk* getOrCreateChunk(int x, int y, int z);
    VoxelChunk *getOrCreateChunk(const glm::ivec3 &pos);

    VoxelChunk* getChunk(int x, int y, int z);
    VoxelChunk *getChunk(const glm::ivec3 &pos);

    static ChunkCoord toChunkCoord(int x, int y, int z);
    static ChunkCoord toChunkCoord(const glm::ivec3& worldPos);

    static glm::ivec3 toLocalCoord(int x, int y, int z);
    static glm::ivec3 toLocalCoord(const glm::ivec3& position);

    static glm::ivec3 toWorldPos(const glm::ivec3& chunkCoord, const glm::ivec3& localPos);

    void clear();

    void forEachChunk(const std::function<void(const ChunkCoord&, VoxelChunk*)>& func);


private:
    std::unordered_map<ChunkCoord, std::unique_ptr<VoxelChunk>> m_chunks;
};

#endif //PIXLENGINE_VOXELWORLD_H
