//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_VOXEL_TYPE_H
#define PIXLENGINE_VOXEL_TYPE_H

#include <cstdint>
#include <string>
#include <array>

namespace voxel {

    using VoxelID = uint8_t; // 0 = air, max 255 types

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
    enum VoxelTypes : VoxelID {
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
                0x00000000,
                RenderingMode::INVISIBLE,
                0.0f,
                false
        };

        // Terrain blocks
        registry[DIRT] = VoxelTypeDefinition{
                "Dirt Block",
                0x8B4513FF,
                RenderingMode::SOLID,
                0.0f,
                true
        };

        registry[GRASS] = VoxelTypeDefinition{
                "Grass Block",
                0x228B22FF,
                RenderingMode::SOLID,
                0.0f,
                true
        };

        registry[STONE] = VoxelTypeDefinition{
                "Stone Block",
                0x696969FF,
                RenderingMode::SOLID,
                0.0f,
                true
        };

        registry[SAND] = VoxelTypeDefinition{
                "Sand Block",
                0xF4A460FF,
                RenderingMode::SOLID,
                0.0f,
                true
        };

        // Liquid blocks
        registry[WATER] = VoxelTypeDefinition{
                "Water",
                0x1E90FF80,
                RenderingMode::TRANSLUCENT,
                0.0f,
                false
        };

        registry[LAVA] = VoxelTypeDefinition{
                "Lava",
                0xFF4500FF,
                RenderingMode::EMISSIVE,
                0.9f,
                false
        };

        // Building materials
        registry[GLASS] = VoxelTypeDefinition{
                "Glass Block",
                0xF0F8FF90,
                RenderingMode::TRANSLUCENT,
                0.0f,
                true
        };

        registry[WOOD] = VoxelTypeDefinition{
                "Wood Log",
                0x8B4513FF,
                RenderingMode::SOLID,
                0.0f,
                true
        };

        registry[LEAVES] = VoxelTypeDefinition{
                "Leaves",
                0x32CD32C0,
                RenderingMode::TRANSLUCENT,
                0.0f,
                true
        };

        return registry;
    }();

    // Validation functions
    [[nodiscard]] inline constexpr bool isValidVoxelID(VoxelID voxelID) noexcept {
        return voxelID <= MAX_TYPE_ID;
    }

    // Direct accessor functions
    [[nodiscard]] inline const VoxelTypeDefinition& getVoxelTypeDefinition(VoxelID voxelID) noexcept {
        return VOXEL_TYPE_REGISTRY[voxelID];
    }

    [[nodiscard]] inline const std::string& getVoxelDisplayName(VoxelID voxelID) noexcept {
        return VOXEL_TYPE_REGISTRY[voxelID].displayName;
    }

    [[nodiscard]] inline constexpr uint32_t getVoxelColorRGBA(VoxelID voxelID) noexcept {
        return VOXEL_TYPE_REGISTRY[voxelID].colorRGBA;
    }

    [[nodiscard]] inline constexpr RenderingMode getVoxelRenderingMode(VoxelID voxelID) noexcept {
        return VOXEL_TYPE_REGISTRY[voxelID].renderingMode;
    }

    [[nodiscard]] inline constexpr float getVoxelLightEmissionLevel(VoxelID voxelID) noexcept {
        return VOXEL_TYPE_REGISTRY[voxelID].lightEmissionLevel;
    }

    [[nodiscard]] inline constexpr bool doesVoxelHaveCollision(VoxelID voxelID) noexcept {
        return VOXEL_TYPE_REGISTRY[voxelID].hasCollision;
    }

    // Semantic property query functions
    [[nodiscard]] inline constexpr bool isVoxelTransparent(VoxelID voxelID) noexcept {
        const auto renderMode = getVoxelRenderingMode(voxelID);
        return renderMode == RenderingMode::TRANSLUCENT || renderMode == RenderingMode::INVISIBLE;
    }

    [[nodiscard]] inline constexpr bool isVoxelOpaque(VoxelID voxelID) noexcept {
        const auto renderMode = getVoxelRenderingMode(voxelID);
        return renderMode == RenderingMode::SOLID || renderMode == RenderingMode::EMISSIVE;
    }

    [[nodiscard]] inline constexpr bool isVoxelLightEmitting(VoxelID voxelID) noexcept {
        return getVoxelRenderingMode(voxelID) == RenderingMode::EMISSIVE;
    }

    [[nodiscard]] inline constexpr bool isVoxelAir(VoxelID voxelID) noexcept {
        return voxelID == AIR;
    }

    [[nodiscard]] inline constexpr bool isVoxelLiquid(VoxelID voxelID) noexcept {
        return voxelID == WATER || voxelID == LAVA;
    }

    [[nodiscard]] inline constexpr bool isVoxelSolid(VoxelID voxelID) noexcept {
        return !isVoxelAir(voxelID) && !isVoxelLiquid(voxelID);
    }

    // Rendering optimization functions
    [[nodiscard]] inline constexpr bool shouldRenderVoxelFace(VoxelID currentVoxel, VoxelID neighborVoxel) noexcept {
        if (currentVoxel == AIR) return false;
        if (neighborVoxel == AIR) return true;

        if (isVoxelOpaque(currentVoxel) && isVoxelOpaque(neighborVoxel))
            return false;
        return true;
    }

} // namespace voxel

#endif //PIXLENGINE_VOXEL_TYPE_H