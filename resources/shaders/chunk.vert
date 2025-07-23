#version 330 core

layout(location = 1) in ivec3 iPosition;   // Instance voxel position
layout(location = 2) in uint iFaceID;      // Face ID (0 = +Z, 1 = -Z, 2 = +X, 3 = -X, 4 = +Y, 5 = -Y)
layout(location = 3) in uint iVoxelID;     // Voxel type ID

uniform mat4 u_View;
uniform mat4 u_Projection;

// Palette de couleur en texture 1D
uniform sampler1D u_ColorTex;

out vec3 vColor;

vec3 transformFace(vec2 localPos, uint faceID) {
    vec3 pos;
    if (faceID == 0u) {
        pos = vec3(localPos.x, localPos.y, 1.0);
    } else if (faceID == 1u) {
        pos = vec3(1.0 - localPos.x, localPos.y, 0.0);
    } else if (faceID == 2u) {
        pos = vec3(1.0, localPos.y, 1.0 - localPos.x);
    } else if (faceID == 3u) {
        pos = vec3(0.0, localPos.y, localPos.x);
    } else if (faceID == 4u) {
        pos = vec3(localPos.x, 1.0, 1.0 - localPos.y);
    } else {
        pos = vec3(localPos.x, 0.0, localPos.y);
    }
    return pos;
}

void main() {
    vec2 quad[6] = vec2[](
    vec2(0.0, 0.0),
    vec2(1.0, 0.0),
    vec2(1.0, 1.0),
    vec2(0.0, 0.0),
    vec2(1.0, 1.0),
    vec2(0.0, 1.0)
    );

    vec3 faceLocal = transformFace(quad[gl_VertexID], iFaceID);
    vec3 worldPos = vec3(iPosition) + faceLocal;

    gl_Position = u_Projection * u_View * vec4(worldPos, 1.0);

    // Sampling la couleur dans la texture palette
    // Normaliser l'ID entre 0 et 1 (en supposant 256 couleurs max)
    float texCoord = float(iVoxelID) / 255.0;
    vColor = texture(u_ColorTex, texCoord).rgb;
}
