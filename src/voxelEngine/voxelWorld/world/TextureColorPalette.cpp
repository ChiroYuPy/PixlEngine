//
// Created by ChiroYuki on 23/07/2025.
//

#include "voxelEngine/voxelWorld/world/TextureColorPalette.h"

#include "core/Logger.h"
#include "voxelEngine/voxelWorld/voxel/VoxelType.h"

TextureColorPalette::TextureColorPalette() : m_textureID(0), m_colors() {
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_1D, m_textureID);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

TextureColorPalette::~TextureColorPalette() {
    if (m_textureID != 0) {
        glDeleteTextures(1, &m_textureID);
    }
}

void TextureColorPalette::updateFromRegistry() {

    for (size_t i = 0; i < MAX_COLORS; ++i) {
        const Color& c = voxel::getVoxelColor(static_cast<voxel::ID>(i));
        Logger::debug() << "color: " << c.toHexString();
        m_colors[i] = glm::vec4(c.getRf(), c.getGf(), c.getBf(), c.getAf());
    }

    glBindTexture(GL_TEXTURE_1D, m_textureID);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA32F, MAX_COLORS, 0, GL_RGBA, GL_FLOAT, m_colors.data());
}

GLuint TextureColorPalette::getTextureID() const {
    return m_textureID;
}