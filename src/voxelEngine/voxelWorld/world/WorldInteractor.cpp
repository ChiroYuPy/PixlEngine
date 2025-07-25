//
// Created by ChiroYuki on 22/07/2025.
//

#include <format>

#include "voxelEngine/voxelWorld/world/WorldInteractor.h"
#include "voxelEngine/voxelWorld/world/World.h"
#include "voxelEngine/voxelWorld/world/WorldRenderer.h"
#include "core/Logger.h"

WorldInteractor::WorldInteractor(World& world, WorldRenderer& chunkRenderer)
        : m_world(world), m_chunkRenderer(chunkRenderer), m_selectedBlockType(voxel::DIRT) {
    m_raycaster = std::make_unique<VoxelRaycaster>(world);
}

bool WorldInteractor::placeBlock(const glm::vec3& cameraPos, const glm::vec3& cameraDirection) {
    auto hit = m_raycaster->raycastFromCamera(cameraPos, cameraDirection);
    if (!hit) return false;

    glm::ivec3 placePos = hit->blockPos + hit->normalFace;

    return placeBlockAt(placePos, m_selectedBlockType);
}

bool WorldInteractor::breakBlock(const glm::vec3& cameraPos, const glm::vec3& cameraDirection) {
    auto hit = m_raycaster->raycastFromCamera(cameraPos, cameraDirection);
    if (!hit) return false;

    return breakBlockAt(hit->blockPos);
}

bool WorldInteractor::placeBlockAt(const glm::ivec3& position, int blockType) {
    if (m_world.getVoxel(position.x, position.y, position.z) != voxel::AIR) {
        Logger::warn() << "Cannot place block: position already occupied";
        return false;
    }

    m_world.setVoxel(position.x, position.y, position.z, blockType);

    m_chunkRenderer.buildAll();

    Logger::info() << std::format("Block placed at ({}, {}, {})", position.x, position.y, position.z);
    return true;
}

bool WorldInteractor::breakBlockAt(const glm::ivec3& position) {
    if (m_world.getVoxel(position.x, position.y, position.z) == voxel::AIR) {
        Logger::warn() << "Cannot break block: no block at position";
        return false;
    }

    m_world.setVoxel(position.x, position.y, position.z, voxel::AIR);

    m_chunkRenderer.buildAll();

    Logger::info() << std::format("Block broken at ({}, {}, {})", position.x, position.y, position.z);
    return true;
}

std::optional<RaycastHit> WorldInteractor::getTargetedBlock(const glm::vec3& cameraPos,
                                                            const glm::vec3& cameraDirection) const {
    return m_raycaster->raycastFromCamera(cameraPos, cameraDirection);
}