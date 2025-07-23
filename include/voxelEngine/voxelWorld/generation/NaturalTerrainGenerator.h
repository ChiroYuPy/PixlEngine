//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_NATURALTERRAINGENERATOR_H
#define PIXLENGINE_NATURALTERRAINGENERATOR_H

#include "ITerrainGenerator.h"
#include "OS2.hpp"

enum class BiomeType : int {
    OCEAN = 0,
    BEACH = 1,
    PLAINS = 2,
    FOREST = 3,
    DESERT = 4,
    MOUNTAINS = 5,
    SWAMP = 6,
    TUNDRA = 7
};

struct BiomeData {
    voxel::ID surfaceBlock;
    voxel::ID subSurfaceBlock;
    voxel::ID deepBlock;
    bool hasWater;
    bool hasTrees;
    bool hasOres;
    double treeChance;
};

class NaturalTerrainGenerator : public ITerrainGenerator {
private:
    OS2 noise;

    BiomeType getBiome(const glm::ivec3 &worldPos, double elevation);
    double getCaveNoise(const glm::ivec3 &worldPos);
    voxel::ID getOreType(const glm::ivec3 &worldPos, double depth);
    bool shouldGenerateTree(const glm::ivec3 &worldPos, const BiomeData &biome);
    void generateTree(Chunk &voxelChunk, const glm::ivec3 &localPos, const glm::ivec3 &chunkPos);

public:
    explicit NaturalTerrainGenerator(uint32_t seed) : ITerrainGenerator(seed) {}

    voxel::ID generateVoxel(const glm::ivec3 &worldPos) override;
    void generateChunk(Chunk &voxelChunk) override;
};

#endif //PIXLENGINE_NATURALTERRAINGENERATOR_H
