//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_COLOR_H
#define PIXLENGINE_COLOR_H

#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "GLT.h"

class Color {
private:
    uint8_t r, g, b, a;

    static float clamp(float v);

public:
    // --- Constructeurs ---
    Color();
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    // --- Méthodes de construction (style builder/static) ---
    static Color fromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    static Color fromFloatRGBA(float r, float g, float b, float a = 1.0f);
    static Color fromHex(uint32_t hexValue, bool hasAlpha = false);
    static Color fromHexString(const std::string &hexString);

    // --- Getters (uint8) ---
    [[nodiscard]] uint8_t getR() const;
    [[nodiscard]] uint8_t getG() const;
    [[nodiscard]] uint8_t getB() const;
    [[nodiscard]] uint8_t getA() const;

    // --- Getters (float) ---
    [[nodiscard]] float getRf() const;
    [[nodiscard]] float getGf() const;
    [[nodiscard]] float getBf() const;
    [[nodiscard]] float getAf() const;

    // --- Conversions ---
    [[nodiscard]] glm::vec3 toVec3() const;
    [[nodiscard]] glm::vec4 toVec4() const;
    [[nodiscard]] uint32_t toHex(bool includeAlpha = false) const;
    [[nodiscard]] std::string toHexString(bool includeAlpha = false) const;
};

#endif //PIXLENGINE_COLOR_H