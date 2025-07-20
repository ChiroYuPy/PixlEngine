//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/voxelWorld/storage/PaletteVoxelStorage.h"

#include <algorithm>
#include <cmath>


PaletteVoxelStorage::PaletteVoxelStorage() : bitsPerVoxel(1) {
    localPalette.push_back(Voxel(0)); // Air par défaut
    resizeData();
}

constexpr int PaletteVoxelStorage::index(int x, int y, int z) {
    return (y << 8) | (z << 4) | x; // y*256 + z*16 + x
}

Voxel PaletteVoxelStorage::get(int x, int y, int z) const {
    int idx = index(x, y, z);
    int paletteIndex = extractBits(idx);
    return localPalette[paletteIndex];
}

void PaletteVoxelStorage::set(int x, int y, int z, Voxel voxel) {
    int paletteIndex = findOrAddToPalette(voxel);
    int idx = index(x, y, z);
    setBits(idx, paletteIndex);
}

int PaletteVoxelStorage::findOrAddToPalette(const Voxel& voxel) {
    auto it = std::find(localPalette.begin(), localPalette.end(), voxel);

    if (it != localPalette.end()) {
        return std::distance(localPalette.begin(), it);
    }

    localPalette.push_back(voxel);
    int newSize = localPalette.size();

    // Redimensionner si nécessaire
    int requiredBits = std::max(1, static_cast<int>(std::ceil(std::log2(newSize))));
    if (requiredBits > bitsPerVoxel) {
        resize(requiredBits);
    }

    return newSize - 1;
}

void PaletteVoxelStorage::resize(int newBitsPerVoxel) {
    if (newBitsPerVoxel == bitsPerVoxel) return;

    std::vector<uint64_t> oldData = std::move(data);
    bitsPerVoxel = newBitsPerVoxel;
    resizeData();

    // Copier les données avec le nouveau format
    for (int i = 0; i < VOLUME; ++i) {
        int oldValue = extractBitsFromData(oldData, i,
                                           std::max(1, static_cast<int>(std::ceil(std::log2(localPalette.size() - 1)))));
        setBits(i, oldValue);
    }
}

void PaletteVoxelStorage::resizeData() {
    int totalBits = VOLUME * bitsPerVoxel;
    int requiredLongs = (totalBits + 63) / 64;
    data.assign(requiredLongs, 0);
}

int PaletteVoxelStorage::extractBits(int voxelIndex) const {
    int bitIndex = voxelIndex * bitsPerVoxel;
    int longIndex = bitIndex / 64;
    int bitOffset = bitIndex % 64;

    uint64_t mask = (1ULL << bitsPerVoxel) - 1;

    if (bitOffset + bitsPerVoxel <= 64) {
        return static_cast<int>((data[longIndex] >> bitOffset) & mask);
    } else {
        // Valeur répartie sur deux uint64_t
        int bitsInFirstLong = 64 - bitOffset;
        int bitsInSecondLong = bitsPerVoxel - bitsInFirstLong;

        uint64_t firstPart = (data[longIndex] >> bitOffset) & ((1ULL << bitsInFirstLong) - 1);
        uint64_t secondPart = data[longIndex + 1] & ((1ULL << bitsInSecondLong) - 1);

        return static_cast<int>(firstPart | (secondPart << bitsInFirstLong));
    }
}

void PaletteVoxelStorage::setBits(int voxelIndex, int value) {
    int bitIndex = voxelIndex * bitsPerVoxel;
    int longIndex = bitIndex / 64;
    int bitOffset = bitIndex % 64;

    uint64_t mask = (1ULL << bitsPerVoxel) - 1;
    uint64_t valueMasked = static_cast<uint64_t>(value) & mask;

    if (bitOffset + bitsPerVoxel <= 64) {
        data[longIndex] = (data[longIndex] & ~(mask << bitOffset)) | (valueMasked << bitOffset);
    } else {
        // Valeur répartie sur deux uint64_t
        int bitsInFirstLong = 64 - bitOffset;
        int bitsInSecondLong = bitsPerVoxel - bitsInFirstLong;

        uint64_t firstMask = ((1ULL << bitsInFirstLong) - 1) << bitOffset;
        uint64_t secondMask = (1ULL << bitsInSecondLong) - 1;

        data[longIndex] = (data[longIndex] & ~firstMask) | ((valueMasked & ((1ULL << bitsInFirstLong) - 1)) << bitOffset);
        data[longIndex + 1] = (data[longIndex + 1] & ~secondMask) | ((valueMasked >> bitsInFirstLong) & secondMask);
    }
}

int PaletteVoxelStorage::extractBitsFromData(const std::vector<uint64_t>& dataArray, int voxelIndex, int bits) const {
    int bitIndex = voxelIndex * bits;
    int longIndex = bitIndex / 64;
    int bitOffset = bitIndex % 64;

    if (longIndex >= dataArray.size()) return 0;

    uint64_t mask = (1ULL << bits) - 1;

    if (bitOffset + bits <= 64) {
        return static_cast<int>((dataArray[longIndex] >> bitOffset) & mask);
    } else {
        int bitsInFirstLong = 64 - bitOffset;
        int bitsInSecondLong = bits - bitsInFirstLong;

        uint64_t firstPart = (dataArray[longIndex] >> bitOffset) & ((1ULL << bitsInFirstLong) - 1);
        uint64_t secondPart = (longIndex + 1 < dataArray.size()) ?
                              dataArray[longIndex + 1] & ((1ULL << bitsInSecondLong) - 1) : 0;

        return static_cast<int>(firstPart | (secondPart << bitsInFirstLong));
    }
}

void PaletteVoxelStorage::clear() {
    localPalette.clear();
    localPalette.push_back(Voxel(0));
    bitsPerVoxel = 1;
    resizeData();
}

double PaletteVoxelStorage::getMemoryUsage() {
    return (data.size() * sizeof(uint64_t)) +
           (localPalette.size() * sizeof(Voxel)) +
           sizeof(*this);
}