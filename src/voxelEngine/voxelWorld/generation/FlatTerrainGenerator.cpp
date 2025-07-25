//
// Created by ChiroYuki on 22/07/2025.
//

#include <iostream>
#include <format>
#include "voxelEngine/voxelWorld/generation/FlatTerrainGenerator.h"
#include "core/Logger.h"

voxel::ID FlatTerrainGenerator::generateVoxel(const glm::ivec3 &worldPos) {
    if (worldPos.y < HEIGHT - 1) return voxel::DIRT;
    else if (worldPos.y == HEIGHT - 1) return voxel::GRASS;
    else return voxel::AIR;
}

void FlatTerrainGenerator::generateChunk(Chunk &voxelChunk) {
    const glm::ivec3 chunkPos = voxelChunk.getPosition();
    Logger::info() << std::format("chunkPos: {}, {}, {}", chunkPos.x, chunkPos.y, chunkPos.z);

    for (int y = 0; y < VoxelArray::SIZE; ++y) {
        int worldY = chunkPos.y * VoxelArray::SIZE + y;
        for (int x = 0; x < VoxelArray::SIZE; ++x) {
            int worldX = chunkPos.x * VoxelArray::SIZE + x;
            for (int z = 0; z < VoxelArray::SIZE; ++z) {
                int worldZ = chunkPos.z * VoxelArray::SIZE + z;
                glm::ivec3 worldPos(worldX, worldY, worldZ);
                voxel::ID voxelID = generateVoxel(worldPos);
                voxelChunk.set({x, y, z}, voxelID);
            }
        }
    }
}