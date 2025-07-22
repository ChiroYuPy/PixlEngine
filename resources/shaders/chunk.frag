#version 330 core
in vec3 vColor;
in vec3 vNormal;
in vec3 vFragPos;

out vec4 color;

void main() {
    // Lumière directionnelle codée en dur (venant d'en haut à gauche)
    vec3 lightDir = normalize(vec3(-0.5, -1.0, -0.3));

    // Couleur de la lumière
    vec3 lightColor = vec3(1.0);
    float ambientStrength = 0.2;

    // Lumière ambiante
    vec3 ambient = ambientStrength * lightColor;

    // Lumière diffuse (Lambert)
    vec3 norm = normalize(vNormal);
    float diff = max(dot(norm, -lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Couleur finale
    vec3 result = (ambient + diffuse) * vColor;
    color = vec4(result, 1.0);
}
