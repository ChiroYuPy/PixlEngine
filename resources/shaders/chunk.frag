#version 330 core

in vec4 vColor;
flat in vec3 vNormal;

out vec4 FragColor;

void main() {
    float shade = 1.0;

    // Pour éviter == sur vec3, on fait un test approximatif
    if (vNormal.y > 0.9) shade = 1.0;        // +Y
    else if (vNormal.y < -0.9) shade = 0.4;  // -Y
    else if (vNormal.x > 0.9) shade = 0.85;  // +X
    else if (vNormal.x < -0.9) shade = 0.75; // -X
    else if (vNormal.z > 0.9) shade = 0.9;   // +Z
    else if (vNormal.z < -0.9) shade = 0.7;  // -Z

    FragColor = vec4(vColor.rgb * shade, vColor.a);
}
