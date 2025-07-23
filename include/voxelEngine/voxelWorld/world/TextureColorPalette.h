//
// Created by ChiroYuki on 23/07/2025.
//

#ifndef PIXLENGINE_TEXTURECOLORPALETTE_H
#define PIXLENGINE_TEXTURECOLORPALETTE_H

#include <array>
#include "GLT.h"

class TextureColorPalette {
public:
    static constexpr size_t MAX_COLORS = 255;

    TextureColorPalette();
    ~TextureColorPalette();

    void updateFromRegistry();

    GLuint getTextureID() const;

private:
    std::array<glm::vec4, MAX_COLORS> m_colors;
    GLuint m_textureID;
};

#endif //PIXLENGINE_TEXTURECOLORPALETTE_H
