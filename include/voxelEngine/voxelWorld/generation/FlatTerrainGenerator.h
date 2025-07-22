//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_FLATTERRAINGENERATOR_H
#define PIXLENGINE_FLATTERRAINGENERATOR_H

#include "ITerrainGenerator.h"

class FlatTerrainGenerator : public ITerrainGenerator {
public:
    explicit FlatTerrainGenerator(uint32_t seed) : ITerrainGenerator(seed) {}

    voxel::ID generateVoxel(const glm::ivec3& worldPos) override;

    void generateChunk(Chunk& voxelChunk) override;

private:
    static constexpr int HEIGHT = 4;
};

#endif //PIXLENGINE_FLATTERRAINGENERATOR_H
