//
// Created by ChiroYuki on 22/07/2025.
//

#include "core/Color.h"

float Color::clamp(float v) {
    return glm::clamp(v, 0.0f, 1.0f);
}

Color::Color() : r(0), g(0), b(0), a(255) {}

Color::Color(uint8_t rr, uint8_t gg, uint8_t bb, uint8_t aa)
        : r(rr), g(gg), b(bb), a(aa) {}

Color Color::fromRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return {r, g, b, a};
}

Color Color::fromFloatRGBA(float rf, float gf, float bf, float af) {
    rf = clamp(rf);
    gf = clamp(gf);
    bf = clamp(bf);
    af = clamp(af);
    return {
            static_cast<uint8_t>(rf * 255.0f),
            static_cast<uint8_t>(gf * 255.0f),
            static_cast<uint8_t>(bf * 255.0f),
            static_cast<uint8_t>(af * 255.0f)
    };
}

Color Color::fromHex(uint32_t hexValue, bool hasAlpha) {
    if (hasAlpha) {
        return Color(
                (hexValue >> 24) & 0xFF,
                (hexValue >> 16) & 0xFF,
                (hexValue >> 8) & 0xFF,
                (hexValue >> 0) & 0xFF
        );
    } else {
        return Color(
                (hexValue >> 16) & 0xFF,
                (hexValue >> 8) & 0xFF,
                (hexValue >> 0) & 0xFF,
                255
        );
    }
}

Color Color::fromHexString(const std::string &hexString) {
    std::string str = hexString;
    if (!str.empty() && str[0] == '#')
        str = str.substr(1);

    if (str.length() != 6 && str.length() != 8)
        throw std::invalid_argument("Invalid hex color format. Expected #RRGGBB or #RRGGBBAA");

    uint32_t hex = std::stoul(str, nullptr, 16);
    if (str.length() == 6) {
        return fromHex(hex, false);
    } else {
        return fromHex(hex, true);
    }
}

uint8_t Color::getR() const { return r; }
uint8_t Color::getG() const { return g; }
uint8_t Color::getB() const { return b; }
uint8_t Color::getA() const { return a; }

float Color::getRf() const { return static_cast<float>(r) / 255.0f; }
float Color::getGf() const { return static_cast<float>(g) / 255.0f; }
float Color::getBf() const { return static_cast<float>(b) / 255.0f; }
float Color::getAf() const { return static_cast<float>(a) / 255.0f; }

glm::vec3 Color::toVec3() const { return {getRf(), getGf(), getBf()}; }
glm::vec4 Color::toVec4() const { return {getRf(), getGf(), getBf(), getAf()}; }

uint32_t Color::toHex(bool includeAlpha) const {
    if (includeAlpha)
        return (r << 24) | (g << 16) | (b << 8) | a;
    else
        return (r << 16) | (g << 8) | b;
}

std::string Color::toHexString(bool includeAlpha) const {
    std::stringstream ss;
    ss << "#" << std::hex << std::setfill('0') << std::uppercase;
    ss << std::setw(2) << static_cast<int>(r)
       << std::setw(2) << static_cast<int>(g)
       << std::setw(2) << static_cast<int>(b);
    if (includeAlpha)
        ss << std::setw(2) << static_cast<int>(a);
    return ss.str();
}