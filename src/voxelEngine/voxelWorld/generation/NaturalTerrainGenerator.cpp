//
// Created by ChiroYuki on 22/07/2025.
//

#include <format>
#include "voxelEngine/voxelWorld/generation/NaturalTerrainGenerator.h"
#include "utils/Logger.h"

voxel::ID NaturalTerrainGenerator::generateVoxel(const glm::ivec3 &worldPos) {
    double nx = static_cast<double>(worldPos.x) * 0.01;
    double nz = static_cast<double>(worldPos.z) * 0.01;

    double elevation = noise.noise2(nx, nz);
    int groundHeight = static_cast<int>(HEIGHT + elevation * 16.0);

    if (worldPos.y < groundHeight - 3) return voxel::STONE;
    if (worldPos.y < groundHeight - 1) return voxel::DIRT;
    if (worldPos.y == groundHeight - 1) return voxel::GRASS;
    return voxel::AIR;
}

void NaturalTerrainGenerator::generateChunk(Chunk &voxelChunk) {
    const glm::ivec3 chunkPos = voxelChunk.getPosition();
    Logger::info(std::format("chunkPos: {}, {}, {}", chunkPos.x, chunkPos.y, chunkPos.z));

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