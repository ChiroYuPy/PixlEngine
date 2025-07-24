//
// Created by ChiroYuki on 22/07/2025.
//

#ifndef PIXLENGINE_COLORUTILS_H
#define PIXLENGINE_COLORUTILS_H

#include "math/Color.h"

namespace utils {
    inline Color blend(const Color &c1, const Color &c2, float t) {
        float r = c1.getRf() * (1 - t) + c2.getRf() * t;
        float g = c1.getGf() * (1 - t) + c2.getGf() * t;
        float b = c1.getBf() * (1 - t) + c2.getBf() * t;
        float a = c1.getAf() * (1 - t) + c2.getAf() * t;
        return Color(r, g, b, a);
    }

    inline float luminance(const Color &c) {
        return 0.2126f * c.getRf() + 0.7152f * c.getGf() + 0.0722f * c.getBf();
    }

    inline Color invert(const Color &c) {
        return Color(255 - c.getR(), 255 - c.getG(), 255 - c.getB(), c.getA());
    }

    inline Color grayscale(const Color &c) {
        uint8_t gray = static_cast<uint8_t>(luminance(c) * 255.0f);
        return Color(gray, gray, gray, c.getA());
    }
}

#endif //PIXLENGINE_COLORUTILS_H
