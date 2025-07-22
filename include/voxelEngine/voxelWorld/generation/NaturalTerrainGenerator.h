//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_NATURALTERRAINGENERATOR_H
#define PIXLENGINE_NATURALTERRAINGENERATOR_H

#include "ITerrainGenerator.h"
#include "OS2.hpp"

class NaturalTerrainGenerator : public ITerrainGenerator {
public:
    explicit NaturalTerrainGenerator(uint32_t seed) : ITerrainGenerator(seed) {}

    voxel::ID generateVoxel(const glm::ivec3& worldPos) override;

    void generateChunk(Chunk& voxelChunk) override;

private:
    OpenSimplex2S noise;
    static constexpr int HEIGHT = 8;
};

#endif //PIXLENGINE_NATURALTERRAINGENERATOR_H
