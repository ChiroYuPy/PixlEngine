//
// Created by ChiroYuki on 22/07/2025.
//

#include <format>

#include "voxelEngine/voxelWorld/world/BlockPlacer.h"
#include "voxelEngine/voxelWorld/world/World.h"
#include "voxelEngine/voxelWorld/world/ChunkRenderer.h"
#include "utils/Logger.h"

BlockPlacer::BlockPlacer(World& world, ChunkRenderer& chunkRenderer)
        : m_world(world), m_chunkRenderer(chunkRenderer), m_selectedBlockType(1) {
    m_raycaster = std::make_unique<VoxelRaycaster>(world, 10.0f);
}

bool BlockPlacer::placeBlock(const glm::vec3& cameraPos, const glm::vec3& cameraDirection, int blockType) {
    auto hit = m_raycaster->raycastFromCamera(cameraPos, cameraDirection);
    if (!hit) {
        return false; // Aucun bloc visé
    }

    // Calculer la position où placer le nouveau bloc (face adjacente)
    glm::ivec3 placePos = hit->blockPos + hit->normalFace;

    return placeBlockAt(placePos, blockType);
}

bool BlockPlacer::breakBlock(const glm::vec3& cameraPos, const glm::vec3& cameraDirection) {
    auto hit = m_raycaster->raycastFromCamera(cameraPos, cameraDirection);
    if (!hit) {
        return false; // Aucun bloc visé
    }

    return breakBlockAt(hit->blockPos);
}

bool BlockPlacer::placeBlockAt(const glm::ivec3& position, int blockType) {
    if (m_world.getVoxel(position.x, position.y, position.z) != 0) {
        Logger::warn("Cannot place block: position already occupied");
        return false;
    }

    m_world.setVoxel(position.x, position.y, position.z, blockType);

    m_chunkRenderer.buildAll();

    Logger::info(std::format("Block placed at ({}, {}, {})", position.x, position.y, position.z));
    return true;
}

bool BlockPlacer::breakBlockAt(const glm::ivec3& position) {
    if (m_world.getVoxel(position.x, position.y, position.z) == 0) {
        Logger::warn("Cannot break block: no block at position");
        return false;
    }

    m_world.setVoxel(position.x, position.y, position.z, 0);

    m_chunkRenderer.buildAll();

    Logger::info(std::format("Block broken at ({}, {}, {})", position.x, position.y, position.z));
    return true;
}

std::optional<RaycastHit> BlockPlacer::getTargetedBlock(const glm::vec3& cameraPos,
                                                        const glm::vec3& cameraDirection) const {
    return m_raycaster->raycastFromCamera(cameraPos, cameraDirection);
}