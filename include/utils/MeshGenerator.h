//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_MESHGENERATOR_H
#define PIXLENGINE_MESHGENERATOR_H

#include <vector>
#include "graphics/Mesh.h"
#include "voxelEngine/voxelWorld/utils/DirectionUtils.h"

class MeshGenerator {
public:
    static std::vector<VertexPosColor> generateCube(float size = 1.0f, const glm::vec3& color = glm::vec3(1.0f));
    static std::vector<unsigned int> getCubeIndices();

    static std::vector<VertexPosColor> generatePlane(float width = 1.0f, float height = 1.0f);
    static std::vector<unsigned int> getPlaneIndices();

    // Pour les voxels optimisés (avec culling des faces)
    static void addCubeFace(std::vector<VertexPosColor>& vertices, std::vector<unsigned int>& indices,
                            const glm::vec3& position, CubicDirection faceIndex, const glm::vec3& color);
};

#endif //PIXLENGINE_MESHGENERATOR_H
