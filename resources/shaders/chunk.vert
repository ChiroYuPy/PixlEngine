#version 430 core

layout(location = 1) in uint iData;

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform vec3 u_chunkPos;
uniform sampler1D u_ColorTex;

out vec4 vColor;
flat out vec3 vNormal;

// Normales associées aux faces
const vec3 NORMALS[6] = vec3[](
vec3( 0.0,  0.0,  1.0),  // +Z (faceID = 0)
vec3( 0.0,  0.0, -1.0),  // -Z (faceID = 1)
vec3( 1.0,  0.0,  0.0),  // +X (faceID = 2)
vec3(-1.0,  0.0,  0.0),  // -X (faceID = 3)
vec3( 0.0,  1.0,  0.0),  // +Y (faceID = 4)
vec3( 0.0, -1.0,  0.0)   // -Y (faceID = 5)
);

// Quad local pour une face (6 vertices pour 2 triangles)
const vec2 QUAD[6] = vec2[](
vec2(0.0, 0.0),  // Triangle 1
vec2(1.0, 0.0),
vec2(1.0, 1.0),
vec2(0.0, 0.0),  // Triangle 2
vec2(1.0, 1.0),
vec2(0.0, 1.0)
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
    // DÉCODAGE CORRIGÉ - doit correspondre exactement à l'encodage
    uint x       = (iData >>  0u) & 31u;   // Bits 0-4
    uint y       = (iData >>  5u) & 31u;   // Bits 5-9
    uint z       = (iData >> 10u) & 31u;   // Bits 10-14
    uint faceID  = (iData >> 15u) & 7u;    // Bits 15-17
    uint voxelID = (iData >> 18u) & 255u;  // Bits 18-25

    // Conversion en coordonnées de voxel locales au chunk
    vec3 voxelPos = vec3(float(x), float(y), float(z));

    // Obtenir la position du vertex sur la face
    vec3 faceOffset = transformFace(QUAD[gl_VertexID], faceID);

    // Position mondiale = position chunk + position voxel local + offset de face
    vec3 worldPos = u_chunkPos + voxelPos + faceOffset;

    gl_Position = u_Projection * u_View * vec4(worldPos, 1.0);

    // Récupération de la couleur via la texture 1D
    float texCoord = float(voxelID) / 255.0;
    vColor = texture(u_ColorTex, texCoord);

    // Assignation de la normale
    vNormal = NORMALS[int(faceID)];
}