#version 330 core

in vec4 v_Color;
flat in uint v_FaceID;

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
    float shade = FACE_SHADES[v_FaceID];
    FragColor = vec4(v_Color.rgb * shade, v_Color.a);
}