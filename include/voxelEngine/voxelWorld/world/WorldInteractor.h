//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_WORLDINTERACTOR_H
#define PIXLENGINE_WORLDINTERACTOR_H

#include <memory>
#include "voxelEngine/voxelWorld/world/VoxelRaycaster.h"

class World;
class ChunkRenderer;
class Camera;

class WorldInteractor {
public:
    WorldInteractor(World& world, ChunkRenderer& chunkRenderer);

    bool placeBlock(const glm::vec3& cameraPos, const glm::vec3& cameraDirection, int blockType = 1);
    bool breakBlock(const glm::vec3& cameraPos, const glm::vec3& cameraDirection);

    bool placeBlockAt(const glm::ivec3& position, int blockType = 1);
    bool breakBlockAt(const glm::ivec3& position);

    void setMaxReach(float reach) { m_raycaster->setMaxDistance(reach); }
    float getMaxReach() const { return m_raycaster->getMaxDistance(); }

    void setSelectedBlockType(int blockType) { m_selectedBlockType = blockType; }
    int getSelectedBlockType() const { return m_selectedBlockType; }

    std::optional<RaycastHit> getTargetedBlock(const glm::vec3& cameraPos,
                                               const glm::vec3& cameraDirection) const;

private:
    World& m_world;
    ChunkRenderer& m_chunkRenderer;
    std::unique_ptr<VoxelRaycaster> m_raycaster;

    int m_selectedBlockType;

    bool placeSphere(const glm::ivec3 &center, int radius, int blockType);

    bool breakSphere(const glm::ivec3 &center, int radius);
};

#endif //PIXLENGINE_WORLDINTERACTOR_H
