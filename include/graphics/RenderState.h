//
// Created by ChiroYuki on 24/07/2025.
//

#ifndef PIXLENGINE_RENDERSTATE_H
#define PIXLENGINE_RENDERSTATE_H

#include "GLT.h"

class RenderState {
public:
    enum class PolygonMode { Fill, Wireframe, Point };
    enum class PolygonFace { Front, Back, FrontAndBack };

    static void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

    static void setClearColor(float r, float g, float b, float a);

    static void clear();

    static void enableDepthTest(bool enable);

    static void enableCullFace(bool enable);

    static void setCullFace(PolygonFace face);

    static void setPolygonMode(PolygonFace face, PolygonMode mode);

    static void enableBlend(bool enable);

    static void setBlendFunc();
};

#endif //PIXLENGINE_RENDERSTATE_H
