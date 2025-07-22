//
// Created by ChiroYuki on 19/07/2025.
//

#include "utils/MeshGenerator.h"

std::vector<VertexPosColor> MeshGenerator::generateCube(float size, const glm::vec3& color) {
    float half = size * 0.5f;

    return {
            // Front face
            {{-half, -half,  half}, color},
            {{ half, -half,  half}, color},
            {{ half,  half,  half}, color},
            {{-half,  half,  half}, color},

            // Back face
            {{ half, -half, -half}, color},
            {{-half, -half, -half}, color},
            {{-half,  half, -half}, color},
            {{ half,  half, -half}, color},

            // Left face
            {{-half, -half, -half}, color},
            {{-half, -half,  half}, color},
            {{-half,  half,  half}, color},
            {{-half,  half, -half}, color},

            // Right face
            {{ half, -half,  half}, color},
            {{ half, -half, -half}, color},
            {{ half,  half, -half}, color},
            {{ half,  half,  half}, color},

            // Top face
            {{-half,  half,  half}, color},
            {{ half,  half,  half}, color},
            {{ half,  half, -half}, color},
            {{-half,  half, -half}, color},

            // Bottom face
            {{-half, -half, -half}, color},
            {{ half, -half, -half}, color},
            {{ half, -half,  half}, color},
            {{-half, -half,  half}, color}
    };
}

std::vector<unsigned int> MeshGenerator::getCubeIndices() {
    return {
            0, 1, 2, 2, 3, 0,       // Front
            4, 5, 6, 6, 7, 4,       // Back
            8, 9, 10, 10, 11, 8,    // Left
            12, 13, 14, 14, 15, 12, // Right
            16, 17, 18, 18, 19, 16, // Top
            20, 21, 22, 22, 23, 20  // Bottom
    };
}

std::vector<VertexPosColor> MeshGenerator::generatePlane(float width, float height) {
    float halfW = width * 0.5f;
    float halfH = height * 0.5f;

    return {
            {{-halfW, 0.0f, -halfH}, glm::vec3(1.0f)},
            {{ halfW, 0.0f, -halfH}, glm::vec3(1.0f)},
            {{ halfW, 0.0f,  halfH}, glm::vec3(1.0f)},
            {{-halfW, 0.0f,  halfH}, glm::vec3(1.0f)}
    };
}

std::vector<unsigned int> MeshGenerator::getPlaneIndices() {
    return {0, 1, 2, 2, 3, 0};
}

void MeshGenerator::addCubeFace(std::vector<VertexPosColor>& vertices, std::vector<unsigned int>& indices,
                                const glm::vec3& position, CubicDirection faceIndex, const glm::vec3& color) {
    float half = 0.5f;
    unsigned int baseIndex = vertices.size();

    // Définir les faces selon l'index
    switch (faceIndex) {
        case CubicDirection::NORTH: // Front (+Z)
            vertices.push_back({{position.x - half, position.y - half, position.z + half}, color});
            vertices.push_back({{position.x + half, position.y - half, position.z + half}, color});
            vertices.push_back({{position.x + half, position.y + half, position.z + half}, color});
            vertices.push_back({{position.x - half, position.y + half, position.z + half}, color});
            break;
        case CubicDirection::SOUTH: // Back (-Z)
            vertices.push_back({{position.x + half, position.y - half, position.z - half}, color});
            vertices.push_back({{position.x - half, position.y - half, position.z - half}, color});
            vertices.push_back({{position.x - half, position.y + half, position.z - half}, color});
            vertices.push_back({{position.x + half, position.y + half, position.z - half}, color});
            break;
        case CubicDirection::EAST: // Left (+X)
            vertices.push_back({{position.x + half, position.y - half, position.z + half}, color});
            vertices.push_back({{position.x + half, position.y - half, position.z - half}, color});
            vertices.push_back({{position.x + half, position.y + half, position.z - half}, color});
            vertices.push_back({{position.x + half, position.y + half, position.z + half}, color});
            break;
        case CubicDirection::WEST: // Right (-X)
            vertices.push_back({{position.x - half, position.y - half, position.z - half}, color});
            vertices.push_back({{position.x - half, position.y - half, position.z + half}, color});
            vertices.push_back({{position.x - half, position.y + half, position.z + half}, color});
            vertices.push_back({{position.x - half, position.y + half, position.z - half}, color});
            break;
        case CubicDirection::UP: // Top (+Y)
            vertices.push_back({{position.x - half, position.y + half, position.z + half}, color});
            vertices.push_back({{position.x + half, position.y + half, position.z + half}, color});
            vertices.push_back({{position.x + half, position.y + half, position.z - half}, color});
            vertices.push_back({{position.x - half, position.y + half, position.z - half}, color});
            break;
        case CubicDirection::DOWN: // Bottom (-Y)
            vertices.push_back({{position.x - half, position.y - half, position.z - half}, color});
            vertices.push_back({{position.x + half, position.y - half, position.z - half}, color});
            vertices.push_back({{position.x + half, position.y - half, position.z + half}, color});
            vertices.push_back({{position.x - half, position.y - half, position.z + half}, color});
            break;
    }

    // Ajouter les indices pour cette face
    indices.insert(indices.end(), {
            baseIndex, baseIndex + 1, baseIndex + 2,
            baseIndex + 2, baseIndex + 3, baseIndex
    });
}