//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_WORLD_H
#define PIXLENGINE_WORLD_H

#include <GLT.h>
#include <memory>
#include <unordered_map>
#include <functional>
#include "voxelEngine/voxelWorld/chunk/Chunk.h"
#include "voxelEngine/voxelWorld/voxel/VoxelType.h"
#include "voxelEngine/voxelWorld/generation/ITerrainGenerator.h"

class World {
public:
    World();
    ~World() = default;

    voxel::ID getVoxel(int worldX, int worldY, int worldZ) const;
    void setVoxel(int worldX, int worldY, int worldZ, voxel::ID ID);

    voxel::ID getVoxel(const glm::ivec3& worldPos) const;
    void setVoxel(const glm::ivec3& worldPos, voxel::ID ID);

    Chunk* getOrCreateChunk(int x, int y, int z);
    Chunk *getOrCreateChunk(const glm::ivec3 &pos);

    Chunk* getChunk(int x, int y, int z);
    Chunk *getChunk(const glm::ivec3 &pos);

    static ChunkCoord toChunkCoord(int x, int y, int z);
    static ChunkCoord toChunkCoord(const glm::ivec3& worldPos);

    static glm::ivec3 toLocalCoord(int x, int y, int z);
    static glm::ivec3 toLocalCoord(const glm::ivec3& position);

    static glm::ivec3 toWorldPos(const glm::ivec3& chunkCoord, const glm::ivec3& localPos = {0, 0, 0});

    void clear();

    void forEachChunk(const std::function<void(const ChunkCoord&, Chunk*)>& func);

    void generateArea(const glm::ivec3& startPos, const glm::ivec3& endPos);

private:
    std::unordered_map<ChunkCoord, std::unique_ptr<Chunk>> m_chunks;

    std::unique_ptr<ITerrainGenerator> m_generator;
};

#endif //PIXLENGINE_WORLD_H
