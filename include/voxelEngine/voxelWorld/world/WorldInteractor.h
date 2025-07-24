//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_WORLDINTERACTOR_H
#define PIXLENGINE_WORLDINTERACTOR_H

#include <memory>
#include "voxelEngine/voxelWorld/world/VoxelRaycaster.h"
#include "voxelEngine/voxelWorld/voxel/VoxelType.h"

class World;
class WorldRenderer;
class Camera;

class WorldInteractor {
public:
    WorldInteractor(World& world, WorldRenderer& chunkRenderer);

    bool placeBlock(const glm::vec3& cameraPos, const glm::vec3& cameraDirection);
    bool breakBlock(const glm::vec3& cameraPos, const glm::vec3& cameraDirection);

    bool placeBlockAt(const glm::ivec3& position, int blockType = 1);
    bool breakBlockAt(const glm::ivec3& position);

    void setMaxReach(float reach) { m_raycaster->setMaxDistance(reach); }
    float getMaxReach() const { return m_raycaster->getMaxDistance(); }

    void setSelectedVoxelID(voxel::ID blockType) { m_selectedBlockType = blockType; }
    int getSelectedBlockType() const { return m_selectedBlockType; }

    std::optional<RaycastHit> getTargetedBlock(const glm::vec3& cameraPos,
                                               const glm::vec3& cameraDirection) const;

private:
    World& m_world;
    WorldRenderer& m_chunkRenderer;
    std::unique_ptr<VoxelRaycaster> m_raycaster;

    voxel::ID m_selectedBlockType;
};

#endif //PIXLENGINE_WORLDINTERACTOR_H
