#version 330 core

in vec3 vColor;
flat in vec3 vNormal;

out vec4 FragColor;

void main() {
    float shade = 1.0;

    // Stylized fixed shading per face direction
    if      (vNormal == vec3( 0.0,  1.0,  0.0)) shade = 1.0;  // +Y (haut)
    else if (vNormal == vec3( 0.0, -1.0,  0.0)) shade = 0.4;  // -Y (bas)
    else if (vNormal == vec3( 1.0,  0.0,  0.0)) shade = 0.85; // +X
    else if (vNormal == vec3(-1.0,  0.0,  0.0)) shade = 0.75; // -X
    else if (vNormal == vec3( 0.0,  0.0,  1.0)) shade = 0.9;  // +Z
    else if (vNormal == vec3( 0.0,  0.0, -1.0)) shade = 0.7;  // -Z

    FragColor = vec4(vColor * shade, 1.0);
}