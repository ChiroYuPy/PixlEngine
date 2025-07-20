//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_MESHGENERATOR_H
#define PIXLENGINE_MESHGENERATOR_H

#include <vector>
#include "graphics/Mesh.h"

class MeshGenerator {
public:
    static std::vector<Vertex> generateCube(float size = 1.0f, const glm::vec3& color = glm::vec3(1.0f));
    static std::vector<unsigned int> getCubeIndices();

    static std::vector<Vertex> generatePlane(float width = 1.0f, float height = 1.0f);
    static std::vector<unsigned int> getPlaneIndices();

    // Pour les voxels optimisés (avec culling des faces)
    static void addCubeFace(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices,
                            const glm::vec3& position, int faceIndex, const glm::vec3& color);
};

#endif //PIXLENGINE_MESHGENERATOR_H
