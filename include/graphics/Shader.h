//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_SHADER_H
#define PIXLENGINE_SHADER_H

#include <string>
#include <unordered_map>
#include <GLT.h>

class Shader {
public:
    Shader() = default;
    ~Shader();

    bool loadFromFiles(const std::string& vertexPath, const std::string& fragmentPath);
    bool loadFromStrings(const std::string& vertexSource, const std::string& fragmentSource);

    void Bind() const;
    void Unbind() const;

    // Uniformes
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec4(const std::string& name, const glm::vec4& value);
    void setMat4(const std::string& name, const glm::mat4& value);

private:
    bool compileShader(const std::string& source, GLenum type, GLuint& shader);
    bool linkProgram(GLuint vertexShader, GLuint fragmentShader);
    int getUniformLocation(const std::string& name);

    GLuint m_program = 0;
    std::unordered_map<std::string, int> m_uniformCache;
};

#endif //PIXLENGINE_SHADER_H
