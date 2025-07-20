//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_PALETTEVOXELSTORAGE_H
#define PIXLENGINE_PALETTEVOXELSTORAGE_H

#include <vector>
#include <bitset>
#include "voxelEngine/voxelWorld/chunk/IVoxelStorage.h"

class PaletteVoxelStorage : public IVoxelStorage {
public:
    PaletteVoxelStorage();

    Voxel get(int x, int y, int z) const override;
    void set(int x, int y, int z, Voxel voxel) override;
    void clear() override;
    double getMemoryUsage() override;

private:
    std::vector<Voxel> localPalette;
    std::vector<uint64_t> data;
    int bitsPerVoxel;

    static constexpr int index(int x, int y, int z);

    int findOrAddToPalette(const Voxel& voxel);
    void resize(int newBitsPerVoxel);
    void resizeData();

    int extractBits(int voxelIndex) const;
    void setBits(int voxelIndex, int value);
    int extractBitsFromData(const std::vector<uint64_t>& dataArray, int voxelIndex, int bits) const;
};

#endif //PIXLENGINE_PALETTEVOXELSTORAGE_H
