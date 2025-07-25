#version 330 core

layout(location = 0) in uint iData;

uniform mat4 u_ViewProjection;
uniform vec3 u_ChunkPos;
uniform sampler1D u_ColorTex;

out vec4 v_Color;
flat out uint v_FaceID;

const vec3 BASE_QUAD[4] = vec3[](
vec3(0.0, 0.0, 1.0),
vec3(1.0, 0.0, 1.0),
vec3(0.0, 0.0, 0.0),
vec3(1.0, 0.0, 0.0)
);

const mat4 FACE_MAT[6] = mat4[](
// +Z (faceID = 0) - Avant
mat4(
vec4(1, 0, 0, 0),
vec4(0, 0, 1, 0),
vec4(0, -1, 0, 0),
vec4(0, 0, 1, 1)
),
// -Z (faceID = 1) - Arrière
mat4(
vec4(1, 0, 0, 0),
vec4(0, 0, -1, 0),
vec4(0, 1, 0, 0),
vec4(0, -1, 0, 1)
),
// +X (faceID = 2) - Droite
mat4(
vec4( 0, -1, 0, 0),
vec4( 1,  0, 0, 0),
vec4( 0,  0, 1, 0),
vec4( 1,  0, 0, 1)
),
// -X (faceID = 3) - Gauche
mat4(
vec4(0, 1, 0, 0),
vec4(-1,  0, 0, 0),
vec4(0,  0, 1, 0),
vec4(0,  -1, 0, 1)
),
// +Y (faceID = 4) - Haut
mat4(
vec4(1, 0, 0, 0),
vec4(0, 1, 0, 0),
vec4(0, 0, 1, 0),
vec4(0, 0, 0, 1)
),
// -Y (faceID = 5) - Bas
mat4(
vec4(1, 0, 0, 0),
vec4(0, -1, 0, 0),
vec4(0, 0, -1, 0),
vec4(0, -1, 1, 1)
)
);

void main() {
    uint x       = (iData >>  0u) & 31u;
    uint y       = (iData >>  5u) & 31u;
    uint z       = (iData >> 10u) & 31u;
    uint faceID  = (iData >> 15u) & 7u;
    uint voxelID = (iData >> 18u) & 255u;
    uint length  = (iData >> 26u) & 31u;

    vec3 voxelPos = vec3(float(x), float(y), float(z));
    vec4 localPos = vec4(BASE_QUAD[gl_VertexID], 1.0);

    localPos.x += float(int(gl_VertexID) % 2) * float(length);

    // Appliquer la matrice de rotation + translation de face
    vec4 faceOffset = FACE_MAT[faceID] * localPos;

    // Ajouter position voxel + chunk
    vec4 worldPos = vec4(u_ChunkPos + voxelPos, 0.0) + faceOffset;

    gl_Position = u_ViewProjection * vec4(worldPos.xyz, 1.0);

    v_Color   = texture(u_ColorTex, float(voxelID) / 255.0);
    v_FaceID  = faceID;
}
