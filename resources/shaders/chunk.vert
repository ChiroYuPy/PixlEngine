#version 430 core

layout(location = 0) in uint iData;

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform vec3 u_ChunkPos;
uniform sampler1D u_ColorTex;

out vec4 vColor;
flat out vec3 vNormal;

// Normales associées aux faces
const vec3 NORMALS[6] = vec3[](
    vec3( 0.0,  0.0,  1.0), // +Z (faceID = 0)
    vec3( 0.0,  0.0, -1.0), // -Z (faceID = 1)
    vec3( 1.0,  0.0,  0.0), // +X (faceID = 2)
    vec3(-1.0,  0.0,  0.0), // -X (faceID = 3)
    vec3( 0.0,  1.0,  0.0), // +Y (faceID = 4)
    vec3( 0.0, -1.0,  0.0)  // -Y (faceID = 5)
);

const vec2 QUAD[4] = vec2[](
    vec2(0.0, 0.0),  // Bottom-left
    vec2(1.0, 0.0),  // Bottom-right
    vec2(0.0, 1.0),  // Top-left
    vec2(1.0, 1.0)   // Top-right
);

// Applique une transformation selon la face
vec3 transformFace(vec2 localPos, uint faceID) {
    if (faceID == 0u) return vec3(localPos.x, localPos.y, 1.0);            // +Z
    else if (faceID == 1u) return vec3(1.0 - localPos.x, localPos.y, 0.0); // -Z
    else if (faceID == 2u) return vec3(1.0, localPos.y, 1.0 - localPos.x); // +X
    else if (faceID == 3u) return vec3(0.0, localPos.y, localPos.x);       // -X
    else if (faceID == 4u) return vec3(localPos.x, 1.0, 1.0 - localPos.y); // +Y
    else return vec3(localPos.x, 0.0, localPos.y);                         // -Y (faceID = 5)
}

void main() {
    uint x       = (iData >>  0u) & 31u;   // Bits 0-4
    uint y       = (iData >>  5u) & 31u;   // Bits 5-9
    uint z       = (iData >> 10u) & 31u;   // Bits 10-14
    uint faceID  = (iData >> 15u) & 7u;    // Bits 15-17
    uint voxelID = (iData >> 18u) & 255u;  // Bits 18-25
    uint length  = (iData >> 26u) & 31u;   // Bits 26-30

    vec3 voxelPos = vec3(float(x), float(y), float(z));
    vec3 chunkPos = u_ChunkPos;

    // Obtenir la position du vertex sur la face
    vec3 faceOffset = transformFace(QUAD[gl_VertexID], faceID);

    // Position mondiale = position chunk + position voxel local + offset de face
    vec3 worldPos = chunkPos + voxelPos + faceOffset;

    gl_Position = u_Projection * u_View * vec4(worldPos, 1.0);

    // Récupération de la couleur via la texture 1D
    float texCoord = float(voxelID) / 255.0;
    vColor = texture(u_ColorTex, texCoord);

    // Assignation de la normale
    vNormal = NORMALS[int(faceID)];
}