#version 330 core

in vec4 vColor;
flat in uint vFaceID;

out vec4 FragColor;

const float FACE_SHADES[6] = float[](
    0.9,  // +Z
    0.7,  // -Z
    0.85, // +X
    0.75, // -X
    1.0,  // +Y
    0.4   // -Y
);

void main() {
    float shade = FACE_SHADES[vFaceID];
    FragColor = vec4(vColor.rgb * shade, vColor.a);
}