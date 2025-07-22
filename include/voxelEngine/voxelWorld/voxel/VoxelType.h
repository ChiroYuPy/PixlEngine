//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_VOXEL_TYPE_H
#define PIXLENGINE_VOXEL_TYPE_H

#include <cstdint>
#include <string>
#include <array>

namespace voxel {

    using ID = uint8_t; // 0 = air, max 255 types

    enum class RenderingMode : uint8_t {
        INVISIBLE,   // Air - not rendered at all
        SOLID,       // Standard opaque block
        TRANSLUCENT, // Glass-like blocks with transparency
        EMISSIVE     // Self-illuminating blocks
    };

    struct VoxelTypeDefinition {
        std::string displayName;
        uint32_t colorRGBA;           // Packed RGBA color 0xRRGGBBAA
        RenderingMode renderingMode;  // How this voxel should be rendered
        float lightEmissionLevel;     // Light emission (0.0 = no light, 1.0 = full bright)
        bool hasCollision;            // Can entities collide with this block?

        // Constructor with sensible defaults
        constexpr VoxelTypeDefinition(
                std::string_view displayName = "Unknown Block",
                uint32_t colorRGBA = 0xFF00FFFF,  // Bright magenta for debugging
                RenderingMode renderingMode = RenderingMode::SOLID,
                float lightEmissionLevel = 0.0f,
                bool hasCollision = true)
        : displayName(displayName),
          colorRGBA(colorRGBA),
          renderingMode(renderingMode),
          lightEmissionLevel(lightEmissionLevel),
          hasCollision(hasCollision) {}
    };

    // voxel type identifiers
    enum VoxelTypes : ID {
        AIR             = 0,
        DIRT            = 1,
        GRASS           = 2,
        STONE           = 3,
        SAND            = 4,
        WATER           = 5,
        LAVA            = 6,
        GLASS           = 7,
        WOOD            = 8,
        LEAVES          = 9,

        MAX_TYPE_ID     = 255
    };

    // Global voxel type registry
    inline const std::array<VoxelTypeDefinition, 256> VOXEL_TYPE_REGISTRY = [] {
        std::array<VoxelTypeDefinition, 256> registry{};

        // Air - special invisible block
        registry[AIR] = VoxelTypeDefinition{
                "Air",
                0x00000000, // fully transparent
                RenderingMode::INVISIBLE,
                0.0f,
                false
        };

        // Terrain blocks
        registry[DIRT] = VoxelTypeDefinition{
                "Dirt Block",
                0x80522FFF, // RGB ~ (128, 82, 47), opaque (alpha=255)
                RenderingMode::SOLID,
                0.0f,
                true
        };

        registry[GRASS] = VoxelTypeDefinition{
                "Grass Block",
                0x7CAC17FF, // RGB ~ (124, 172, 23) vert herbe typique
                RenderingMode::SOLID,
                0.0f,
                true
        };

        registry[STONE] = VoxelTypeDefinition{
                "Stone Block",
                0x7F7F7FFF, // RGB ~ (127, 127, 127) gris moyen
                RenderingMode::SOLID,
                0.0f,
                true
        };

        registry[SAND] = VoxelTypeDefinition{
                "Sand Block",
                0xFAF0CFFF, // RGB ~ (250, 240, 207) sable clair
                RenderingMode::SOLID,
                0.0f,
                true
        };

        // Liquid blocks
        registry[WATER] = VoxelTypeDefinition{
                "Water",
                0x3F76E480, // RGB ~ (63, 118, 228), alpha 128 (~50% transparent)
                RenderingMode::TRANSLUCENT,
                0.0f,
                false
        };

        registry[LAVA] = VoxelTypeDefinition{
                "Lava",
                0xCF4A0FFF, // RGB ~ (207, 74, 15) vif, opaque
                RenderingMode::EMISSIVE,
                0.9f,
                false
        };

        // Building materials
        registry[GLASS] = VoxelTypeDefinition{
                "Glass Block",
                0xFFFFFF40, // blanc très transparent (alpha ~ 64 / 255)
                RenderingMode::TRANSLUCENT,
                0.0f,
                true
        };

        registry[WOOD] = VoxelTypeDefinition{
                "Wood Log",
                0x6B4F2FFF, // RGB ~ (107, 79, 47) marron bois
                RenderingMode::SOLID,
                0.0f,
                true
        };

        registry[LEAVES] = VoxelTypeDefinition{
                "Leaves",
                0x4C9B23A0, // RGB ~ (76, 155, 35) vert feuille, alpha ~160 (semi transparent)
                RenderingMode::TRANSLUCENT,
                0.0f,
                true
        };

        return registry;
    }();

    // Validation functions
    [[nodiscard]] inline constexpr bool isValidVoxelID(ID voxelID) noexcept {
        return voxelID <= MAX_TYPE_ID;
    }

    // Direct accessor functions
    [[nodiscard]] inline const VoxelTypeDefinition& getVoxelTypeDefinition(ID voxelID) noexcept {
        return VOXEL_TYPE_REGISTRY[voxelID];
    }

    [[nodiscard]] inline const std::string& getVoxelDisplayName(ID voxelID) noexcept {
        return VOXEL_TYPE_REGISTRY[voxelID].displayName;
    }

    [[nodiscard]] inline constexpr uint32_t getVoxelColorRGBA(ID voxelID) noexcept {
        return VOXEL_TYPE_REGISTRY[voxelID].colorRGBA;
    }

    [[nodiscard]] inline constexpr RenderingMode getVoxelRenderingMode(ID voxelID) noexcept {
        return VOXEL_TYPE_REGISTRY[voxelID].renderingMode;
    }

    [[nodiscard]] inline constexpr float getVoxelLightEmissionLevel(ID voxelID) noexcept {
        return VOXEL_TYPE_REGISTRY[voxelID].lightEmissionLevel;
    }

    [[nodiscard]] inline constexpr bool doesVoxelHaveCollision(ID voxelID) noexcept {
        return VOXEL_TYPE_REGISTRY[voxelID].hasCollision;
    }

    // Semantic property query functions
    [[nodiscard]] inline constexpr bool isVoxelTransparent(ID voxelID) noexcept {
        const auto renderMode = getVoxelRenderingMode(voxelID);
        return renderMode == RenderingMode::TRANSLUCENT || renderMode == RenderingMode::INVISIBLE;
    }

    [[nodiscard]] inline constexpr bool isVoxelOpaque(ID voxelID) noexcept {
        const auto renderMode = getVoxelRenderingMode(voxelID);
        return renderMode == RenderingMode::SOLID || renderMode == RenderingMode::EMISSIVE;
    }

    [[nodiscard]] inline constexpr bool isVoxelLightEmitting(ID voxelID) noexcept {
        return getVoxelRenderingMode(voxelID) == RenderingMode::EMISSIVE;
    }

    [[nodiscard]] inline constexpr bool isVoxelAir(ID voxelID) noexcept {
        return voxelID == AIR;
    }

    [[nodiscard]] inline constexpr bool isVoxelLiquid(ID voxelID) noexcept {
        return voxelID == WATER || voxelID == LAVA;
    }

    [[nodiscard]] inline constexpr bool isVoxelSolid(ID voxelID) noexcept {
        return !isVoxelAir(voxelID) && !isVoxelLiquid(voxelID);
    }

    // Rendering optimization functions
    [[nodiscard]] inline constexpr bool shouldRenderVoxelFace(ID currentVoxel, ID neighborVoxel) noexcept {
        if (currentVoxel == AIR) return false;
        if (neighborVoxel == AIR) return true;

        if (isVoxelOpaque(currentVoxel) && isVoxelOpaque(neighborVoxel))
            return false;
        return true;
    }

} // namespace voxel

#endif //PIXLENGINE_VOXEL_TYPE_H