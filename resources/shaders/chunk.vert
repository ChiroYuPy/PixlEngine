#version 330 core

layout(location = 1) in ivec3 iPosition;   // Instance voxel position
layout(location = 2) in uint iFaceID;      // Face ID (0 = +Z, 1 = -Z, 2 = +X, 3 = -X, 4 = +Y, 5 = -Y)
layout(location = 3) in uint iVoxelID;     // Voxel type ID

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 vColor;

vec3 transformFace(vec2 localPos, uint faceID) {
    // Convert 2D local position to 3D face position
    vec3 pos;

    if (faceID == 0u) {
        // +Z face (front)
        pos = vec3(localPos.x, localPos.y, 1.0);
    } else if (faceID == 1u) {
        // -Z face (back)
        pos = vec3(1.0 - localPos.x, localPos.y, 0.0);
    } else if (faceID == 2u) {
        // +X face (right)
        pos = vec3(1.0, localPos.y, 1.0 - localPos.x);
    } else if (faceID == 3u) {
        // -X face (left)
        pos = vec3(0.0, localPos.y, localPos.x);
    } else if (faceID == 4u) {
        // +Y face (top)
        pos = vec3(localPos.x, 1.0, 1.0 - localPos.y);
    } else {
        // -Y face (bottom)
        pos = vec3(localPos.x, 0.0, localPos.y);
    }

    return pos;
}

vec3 voxelIDToColor(uint id) {
    switch (id) {
        case 1u: return vec3(1.0, 0.0, 0.0);  // Rouge
        case 2u: return vec3(0.0, 1.0, 0.0);  // Vert
        case 3u: return vec3(0.0, 0.0, 1.0);  // Bleu
        case 4u: return vec3(1.0, 1.0, 0.0);  // Jaune
        default: return vec3(1.0, 1.0, 1.0);  // Blanc
    }
}

void main() {
    // Positions du quad (triangle strip en 6 vertices)
    vec2 quad[6] = vec2[](
    vec2(0.0, 0.0),  // Bottom-left
    vec2(1.0, 0.0),  // Bottom-right
    vec2(1.0, 1.0),  // Top-right
    vec2(0.0, 0.0),  // Bottom-left
    vec2(1.0, 1.0),  // Top-right
    vec2(0.0, 1.0)   // Top-left
    );

    // Transform la position locale de la face
    vec3 faceLocal = transformFace(quad[gl_VertexID], iFaceID);

    // Position mondiale = position du voxel + position locale de la face
    vec3 worldPos = vec3(iPosition) + faceLocal;

    gl_Position = u_Projection * u_View * vec4(worldPos, 1.0);
    vColor = voxelIDToColor(iVoxelID);
}