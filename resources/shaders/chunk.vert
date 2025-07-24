#version 430 core

layout(location = 0) in uint iData;

uniform mat4 u_ViewProjection;
uniform vec3 u_ChunkPos;
uniform sampler1D u_ColorTex;

out vec4 vColor;
flat out uint vFaceID; // Passer le faceID au fragment shader

// Table de lookup pour éviter les if/else chains
const vec3 FACE_TRANSFORMS[24] = vec3[](
    // +Z (faceID = 0)
    vec3(0.0, 0.0, 1.0), vec3(1.0, 0.0, 1.0), vec3(0.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0),
    // -Z (faceID = 1)
    vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 0.0), vec3(0.0, 1.0, 0.0),
    // +X (faceID = 2)
    vec3(1.0, 0.0, 1.0), vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 0.0),
    // -X (faceID = 3)
    vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 1.0, 1.0),
    // +Y (faceID = 4)
    vec3(0.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(0.0, 1.0, 0.0), vec3(1.0, 1.0, 0.0),
    // -Y (faceID = 5)
    vec3(0.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), vec3(1.0, 0.0, 1.0)
);

void main() {
    // Extraction des données via bitshifts
    uint x       = (iData >>  0u) & 31u;
    uint y       = (iData >>  5u) & 31u;
    uint z       = (iData >> 10u) & 31u;
    uint faceID  = (iData >> 15u) & 7u;
    uint voxelID = (iData >> 18u) & 255u;

    // Position du voxel
    vec3 voxelPos = vec3(float(x), float(y), float(z));

    // Lookup direct de la transformation de face
    vec3 faceOffset = FACE_TRANSFORMS[faceID * 4u + uint(gl_VertexID)];

    // Position mondiale
    vec3 worldPos = u_ChunkPos + voxelPos + faceOffset;
    gl_Position = u_ViewProjection * vec4(worldPos, 1.0);

    // Couleur via texture lookup
    vColor = texture(u_ColorTex, float(voxelID) / 255.0);

    // Passer le faceID au fragment shader
    vFaceID = faceID;
}