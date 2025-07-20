//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_VOXELCHUNK_H
#define PIXLENGINE_VOXELCHUNK_H


#include <memory>
#include "IVoxelStorage.h"
#include "voxelEngine/voxelWorld/storage/DenseVoxelStorage.h"
#include "voxelEngine/voxelWorld/utils/DirectionUtils.h"

class VoxelChunk {
public:
    explicit VoxelChunk(std::unique_ptr<IVoxelStorage> storage = std::make_unique<DenseVoxelStorage>());

    // Accès aux voxels
    Voxel get(int x, int y, int z) const;
    void set(int x, int y, int z, Voxel voxel);
    void clear();

    // Gestion des voisins
    void setNeighbor(CubicDirection direction, VoxelChunk* neighbor);
    VoxelChunk* getNeighbor(CubicDirection direction) const;

    // Accesseur pour le storage
    IVoxelStorage* getStorage() const { return m_storage.get(); }

private:
    std::unique_ptr<IVoxelStorage> m_storage;
    std::array<VoxelChunk*, 6> m_neighbors;

    static bool isInBounds(int x, int y, int z);
};

#endif //PIXLENGINE_VOXELCHUNK_H
