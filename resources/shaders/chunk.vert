#version 430 core

layout(location = 1) in ivec3 iPosition;   // Instance voxel position
layout(location = 2) in uint iFaceID;      // Face ID (0 = +Z, 1 = -Z, 2 = +X, 3 = -X, 4 = +Y, 5 = -Y)
layout(location = 3) in uint iVoxelID;     // Voxel type ID

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform sampler1D u_ColorTex;

out vec3 vColor;
flat out vec3 vNormal;

vec3 transformFace(vec2 localPos, uint faceID) {
    if (faceID == 0u) return vec3(localPos.x, localPos.y, 1.0);            // +Z
    else if (faceID == 1u) return vec3(1.0 - localPos.x, localPos.y, 0.0); // -Z
    else if (faceID == 2u) return vec3(1.0, localPos.y, 1.0 - localPos.x); // +X
    else if (faceID == 3u) return vec3(0.0, localPos.y, localPos.x);       // -X
    else if (faceID == 4u) return vec3(localPos.x, 1.0, 1.0 - localPos.y); // +Y
    else                     return vec3(localPos.x, 0.0, localPos.y);     // -Y
}

const vec3 NORMALS[6] = vec3[](
vec3( 0.0,  1.0,  0.0), // +Y
vec3( 0.0, -1.0,  0.0), // -Y
vec3( 1.0,  0.0,  0.0), // +X
vec3(-1.0,  0.0,  0.0), // -X
vec3( 0.0,  0.0,  1.0), // +Z
vec3( 0.0,  0.0, -1.0)  // -Z
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

    // Texture color from 1D palette
    float texCoord = float(iVoxelID) / 255.0;
    vColor = texture(u_ColorTex, texCoord).rgb;
    vNormal = NORMALS[iFaceID];
}