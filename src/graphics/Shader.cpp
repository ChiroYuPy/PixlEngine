//
// Created by ChiroYuki on 19/07/2025.
//

#include <fstream>
#include <iostream>
#include <sstream>

#include "graphics/Shader.h"
#include "core/Logger.h"

Shader::~Shader() {
    if (m_program != 0) {
        glDeleteProgram(m_program);
    }
}

bool Shader::loadFromFiles(const std::string& vertexPath, const std::string& fragmentPath) {
    std::ifstream vShaderFile(vertexPath);
    std::ifstream fShaderFile(fragmentPath);

    if (!vShaderFile.is_open() || !fShaderFile.is_open()) {
        Logger::error() << "Failed to open shader files";
        return false;
    }

    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    return loadFromStrings(vShaderStream.str(), fShaderStream.str());
}

bool Shader::loadFromStrings(const std::string& vertexSource, const std::string& fragmentSource) {
    GLuint vertexShader, fragmentShader;

    if (!compileShader(vertexSource, GL_VERTEX_SHADER, vertexShader))
        return false;

    if (!compileShader(fragmentSource, GL_FRAGMENT_SHADER, fragmentShader)) {
        glDeleteShader(vertexShader);
        return false;
    }

    if (!linkProgram(vertexShader, fragmentShader)) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

bool Shader::compileShader(const std::string& source, GLenum type, GLuint& shader) {
    shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        Logger::error() << "Shader compilation failed: " << infoLog;
        return false;
    }

    return true;
}

void Shader::Bind() const {
    if (m_program != 0)
        glUseProgram(m_program);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) {
    int location = getUniformLocation(name);
    if (location >= 0)
        glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

int Shader::getUniformLocation(const std::string& name) {
    auto it = m_uniformCache.find(name);
    if (it != m_uniformCache.end())
        return it->second;

    int location = glGetUniformLocation(m_program, name.c_str());
    m_uniformCache[name] = location;
    return location;
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::setInt(const std::string& name, int value) {
    int location = getUniformLocation(name);
    if (location >= 0)
        glUniform1i(location, value);
}

void Shader::setFloat(const std::string& name, float value) {
    int location = getUniformLocation(name);
    if (location >= 0)
        glUniform1f(location, value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) {
    int location = getUniformLocation(name);
    if (location >= 0)
        glUniform3fv(location, 1, &value[0]);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) {
    int location = getUniformLocation(name);
    if (location >= 0)
        glUniform4fv(location, 1, &value[0]);
}

bool Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);

    GLint success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
        std::cerr << "Shader linking failed: " << infoLog << std::endl;
        glDeleteProgram(m_program);
        m_program = 0;
        return false;
    }

    return true;
}