#version 430 core

layout(location = 1) in ivec3 iPosition;   // Instance voxel position
layout(location = 2) in uint iFaceID;      // Face ID (0=+Z,1=-Z,2=+X,3=-X,4=+Y,5=-Y)
layout(location = 3) in uint iVoxelID;     // Voxel type ID

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform sampler1D u_ColorTex;

out vec4 vColor;
flat out vec3 vNormal;

// Transforme la position locale (quad) selon la face
vec3 transformFace(vec2 localPos, uint faceID) {
    if (faceID == 0u) return vec3(localPos.x, localPos.y, 1.0);            // +Z
    else if (faceID == 1u) return vec3(1.0 - localPos.x, localPos.y, 0.0); // -Z
    else if (faceID == 2u) return vec3(1.0, localPos.y, 1.0 - localPos.x); // +X
    else if (faceID == 3u) return vec3(0.0, localPos.y, localPos.x);       // -X
    else if (faceID == 4u) return vec3(localPos.x, 1.0, 1.0 - localPos.y); // +Y
    else return vec3(localPos.x, 0.0, localPos.y);                         // -Y
}

// Normales associées aux faces (ordre iFaceID)
const vec3 NORMALS[6] = vec3[](
vec3( 0.0,  0.0,  1.0),  // +Z = faceID 0
vec3( 0.0,  0.0, -1.0),  // -Z = faceID 1
vec3( 1.0,  0.0,  0.0),  // +X = faceID 2
vec3(-1.0,  0.0,  0.0),  // -X = faceID 3
vec3( 0.0,  1.0,  0.0),  // +Y = faceID 4
vec3( 0.0, -1.0,  0.0)   // -Y = faceID 5
);

void main() {
    vec2 quad[6] = vec2[](
    vec2(0.0, 0.0),
    vec2(1.0, 0.0),
    vec2(1.0, 1.0),
    vec2(0.0, 0.0),
    vec2(1.0, 1.0),
    vec2(0.0, 1.0)
    );

    vec3 localPos = transformFace(quad[gl_VertexID], iFaceID);
    vec3 worldPos = vec3(iPosition) + localPos;

    gl_Position = u_Projection * u_View * vec4(worldPos, 1.0);

    // Coordonnée pour sampler la texture 1D
    float texCoord = float(iVoxelID) / 255.0;
    vColor = texture(u_ColorTex, texCoord);
    vNormal = NORMALS[iFaceID];
}
