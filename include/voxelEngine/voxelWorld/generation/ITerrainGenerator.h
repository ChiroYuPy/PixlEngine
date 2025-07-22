//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_ITERRAINGENERATOR_H
#define PIXLENGINE_ITERRAINGENERATOR_H

#include <GLT.h>
#include "voxelEngine/voxelWorld/chunk/Chunk.h"

class ITerrainGenerator {
public:
    explicit ITerrainGenerator(uint32_t seed) : m_seed(seed) {}
    virtual ~ITerrainGenerator() = default;

    virtual void generateChunk(Chunk& voxelChunk) = 0;

protected:
    uint32_t m_seed;

    virtual voxel::ID generateVoxel(const glm::ivec3& worldPos) = 0;
};

#endif //PIXLENGINE_ITERRAINGENERATOR_H
