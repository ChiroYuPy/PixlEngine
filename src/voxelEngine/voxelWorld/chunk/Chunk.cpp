//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/voxelWorld/chunk/Chunk.h"
#include "voxelEngine/voxelWorld/world/World.h"

Chunk::Chunk(ChunkCoord coord)
: m_position(coord) {}

bool Chunk::isInBounds(int x, int y, int z) {
    return x >= 0 && x < VoxelArray::SIZE &&
           y >= 0 && y < VoxelArray::SIZE &&
           z >= 0 && z < VoxelArray::SIZE;
}

voxel::ID Chunk::get(int x, int y, int z) const {
    if (!isInBounds(x, y, z)) return voxel::AIR;
    return m_storage.get(x, y, z);
}

voxel::ID Chunk::get(const glm::ivec3& pos) const {
    return get(pos.x, pos.y, pos.z);
}

void Chunk::set(int x, int y, int z, voxel::ID voxel) {
    if (!isInBounds(x, y, z)) return;
    m_storage.set(x, y, z, voxel);
    markDirty();
}

void Chunk::set(const glm::ivec3& pos, voxel::ID voxel) {
    set(pos.x, pos.y, pos.z, voxel);
}

void Chunk::fill(voxel::ID ID) {
    m_storage.fill(ID);
    markDirty();
}

void Chunk::markDirty() {
    m_dirty = true;
}

glm::ivec3 Chunk::getPosition() const {
    return {m_position.x, m_position.y, m_position.z};
}

void Chunk::buildMesh(const World& world) {
    if (!m_dirty) return;

    std::vector<FaceInstance> opaqueFaces;
    std::vector<FaceInstance> transparentFaces;

    for (int x = 0; x < VoxelArray::SIZE; ++x) {
        for (int y = 0; y < VoxelArray::SIZE; ++y) {
            for (int z = 0; z < VoxelArray::SIZE; ++z) {
                voxel::ID voxelID = get(x, y, z);

                if (voxelID == voxel::AIR) continue;

                voxel::RenderMode type = voxel::getRenderMode(voxelID);

                for (uint8_t faceID = 0; faceID < 6; ++faceID) {
                    CubicDirection dir = DirectionUtils::fromIndex(faceID);
                    glm::ivec3 offset = DirectionUtils::getOffset(dir);
                    int nx = x + offset.x, ny = y + offset.y, nz = z + offset.z;

                    voxel::ID neighborVoxelID;

                    if (nx >= 0 && ny >= 0 && nz >= 0 &&
                        nx < VoxelArray::SIZE && ny < VoxelArray::SIZE && nz < VoxelArray::SIZE) {
                        neighborVoxelID = get(nx, ny, nz);
                    } else {
                        int wx = m_position.x * VoxelArray::SIZE + nx;
                        int wy = m_position.y * VoxelArray::SIZE + ny;
                        int wz = m_position.z * VoxelArray::SIZE + nz;
                        neighborVoxelID = world.getVoxel(wx, wy, wz);
                    }

                    bool visible = false;
                    voxel::RenderMode neighborType = voxel::getRenderMode(neighborVoxelID);

                    if (neighborVoxelID == voxel::AIR) {
                        visible = true;
                    }
                    else if (type == voxel::RenderMode::OPAQUE && neighborType == voxel::RenderMode::TRANSPARENT) {
                        visible = true;
                    }
                    else if (type == voxel::RenderMode::TRANSPARENT) {
                        if (neighborType == voxel::RenderMode::TRANSPARENT)
                        if (voxelID != neighborVoxelID) {
                            visible = true;
                        }
                    }

                    if (visible) {
                        const uint8_t length = 0;
                        FaceInstance face = FaceInstance{glm::ivec3(x, y, z), faceID, voxelID, length};

                        switch (type) {
                            case voxel::RenderMode::OPAQUE:
                                opaqueFaces.push_back(face);
                                break;
                            case voxel::RenderMode::TRANSPARENT:
                                transparentFaces.push_back(face);
                                break;
                            default:
                                opaqueFaces.push_back(face); // fallback
                                break;
                        }
                    }
                }
            }
        }
    }

    m_opaqueMesh.uploadInstances(opaqueFaces);
    m_transparentMesh.uploadInstances(transparentFaces);

    m_dirty = false;
}

void Chunk::drawOpaque(Shader& shader) const {
    shader.setVec3("u_ChunkPos", glm::vec3(getPosition()*VoxelArray::SIZE));
    m_opaqueMesh.draw();
}

void Chunk::drawTransparent(Shader& shader) const {
    shader.setVec3("u_ChunkPos", glm::vec3(getPosition()*VoxelArray::SIZE));
    m_transparentMesh.draw();
}