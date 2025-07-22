//
// Created by ChiroYuki on 22/07/2025.
//

#include "voxelEngine/voxelWorld/chunk/ChunkMesh.h"
#include "voxelEngine/voxelWorld/voxel/VoxelArray.h"
#include "core/Application.h"
#include "utils/MeshGenerator.h"
#include "voxelEngine/voxelWorld/world/World.h"
#include "voxelEngine/voxelWorld/chunk/Chunk.h"

ChunkMesh::ChunkMesh(const glm::ivec3& coord) : m_coord(coord) {}

bool ChunkMesh::isValid() const {
    return m_mesh && m_mesh->isValid();
}

void ChunkMesh::build(const Chunk& chunk, const World& world) {
    std::vector<VertexPosColor> vertices;
    std::vector<uint32_t> indices;

    for (int x = 0; x < VoxelArray::SIZE; ++x) {
        for (int y = 0; y < VoxelArray::SIZE; ++y) {
            for (int z = 0; z < VoxelArray::SIZE; ++z) {
                voxel::ID voxel = chunk.get(x, y, z);
                if (voxel == voxel::AIR) continue;

                glm::vec3 pos = glm::vec3(x, y, z);
                glm::vec3 color = voxel::getVoxelColor(voxel).toVec3();

                for (int i = 0; i < 6; ++i) {
                    CubicDirection dir = DirectionUtils::fromIndex(i);
                    glm::ivec3 offset = DirectionUtils::getOffset(dir);
                    int nx = x + offset.x, ny = y + offset.y, nz = z + offset.z;

                    bool exposed = false;
                    if (nx >= 0 && ny >= 0 && nz >= 0 &&
                        nx < VoxelArray::SIZE && ny < VoxelArray::SIZE && nz < VoxelArray::SIZE) {
                        exposed = chunk.get(nx, ny, nz) == voxel::AIR;
                    } else {
                        int wx = m_coord.x * VoxelArray::SIZE + nx;
                        int wy = m_coord.y * VoxelArray::SIZE + ny;
                        int wz = m_coord.z * VoxelArray::SIZE + nz;
                        exposed = world.getVoxel(wx, wy, wz) == voxel::AIR;
                    }

                    if (exposed) {
                        MeshGenerator::addCubeFace(vertices, indices, pos, dir, color);
                    }
                }
            }
        }
    }

    if (!vertices.empty()) {
        m_mesh = std::make_unique<Mesh<VertexPosColor>>();

        m_mesh->setVertexAttribSetup([=]() {
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor),
                                  (void*)offsetof(VertexPosColor, position));

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor),
                                  (void*)offsetof(VertexPosColor, color));
        });

        m_mesh->setData(vertices, indices);
    }
}

void ChunkMesh::render(Shader& shader) const {
    if (!isValid()) return;

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(
            m_coord.x * VoxelArray::SIZE,
            m_coord.y * VoxelArray::SIZE,
            m_coord.z * VoxelArray::SIZE
    ));

    shader.setMat4("u_Model", model);
    Application::getInstance().getRenderer()->drawMesh(*m_mesh, shader, model);
}