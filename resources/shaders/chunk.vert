#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aColor;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 vColor;
out vec3 vNormal;
out vec3 vFragPos;

void main() {
    mat4 modelView = u_View * u_Model;
    vec4 worldPos = u_Model * vec4(aPos, 1.0);
    vFragPos = vec3(worldPos);
    vNormal = mat3(transpose(inverse(u_Model))) * aNormal; // Normale dans l'espace monde
    vColor = aColor;

    gl_Position = u_Projection * u_View * worldPos;
}
