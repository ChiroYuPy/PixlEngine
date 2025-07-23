//
// Created by ChiroYuki on 23/07/2025.
//

#include "voxelEngine/voxelWorld/world/TextureColorPalette.h"
#include "voxelEngine/voxelWorld/voxel/VoxelType.h"

TextureColorPalette::TextureColorPalette() : m_textureID(0) {
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

        m_colors[i] = glm::vec3(c.getRf(), c.getGf(), c.getBf());
    }

    glBindTexture(GL_TEXTURE_1D, m_textureID);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB32F, MAX_COLORS, 0, GL_RGB, GL_FLOAT, m_colors.data());
}

GLuint TextureColorPalette::getTextureID() const {
    return m_textureID;
}