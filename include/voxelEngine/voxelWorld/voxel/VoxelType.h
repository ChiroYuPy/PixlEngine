//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_VOXEL_TYPE_H
#define PIXLENGINE_VOXEL_TYPE_H

#include <cstdint>
#include <string>
#include <array>
#include "core/Color.h"

namespace voxel {

    using ID = uint8_t; // 0 = air, max 255 types

    enum class RenderMode : uint8_t {
        INVISIBLE,   // Air - not rendered at all
        OPAQUE,      // Standard opaque block
        TRANSPARENT, // Glass-like blocks with transparency
        EMISSIVE     // Self-illuminating blocks
    };

    struct VoxelTypeDefinition {
        std::string displayName;
        Color color;
        RenderMode renderMode;
        float lightEmissionLevel;
        bool hasCollision;

        VoxelTypeDefinition(
                std::string_view displayName = "Unknown Block",
                const Color& color = Color(255, 0, 255, 255),
                RenderMode renderingMode = RenderMode::OPAQUE,
                float lightEmissionLevel = 0.0f,
                bool hasCollision = true);
    };

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

    // Classe singleton pour gérer le registre des voxels
    class VoxelTypeRegistry {
    private:
        std::array<VoxelTypeDefinition, 256> registry;
        static VoxelTypeRegistry* instance;

        VoxelTypeRegistry();

    public:
        static VoxelTypeRegistry& getInstance();

        // Accesseurs en lecture seule
        [[nodiscard]] const VoxelTypeDefinition& getDefinition(ID voxelID) const noexcept;

        // Méthodes pour modifier les définitions
        void setDefinition(ID voxelID, const VoxelTypeDefinition& definition) noexcept;
        void setColor(ID voxelID, const Color& color) noexcept;
        void setRenderingMode(ID voxelID, RenderMode mode) noexcept;
        void setLightEmissionLevel(ID voxelID, float level) noexcept;
        void setCollision(ID voxelID, bool hasCollision) noexcept;
        void setDisplayName(ID voxelID, std::string_view name) noexcept;

        // Méthode pour réinitialiser aux valeurs par défaut
        void resetToDefaults() noexcept;
    };

    // Fonctions utilitaires (inchangées mais utilisent maintenant le singleton)
    [[nodiscard]] bool isValidVoxelID(ID voxelID) noexcept;
    [[nodiscard]] const VoxelTypeDefinition& getVoxelTypeDefinition(ID voxelID) noexcept;
    [[nodiscard]] const std::string& getVoxelDisplayName(ID voxelID) noexcept;
    [[nodiscard]] Color getVoxelColor(ID voxelID) noexcept;
    [[nodiscard]] RenderMode getRenderMode(ID voxelID) noexcept;
    [[nodiscard]] float getVoxelLightEmissionLevel(ID voxelID) noexcept;
    [[nodiscard]] bool doesVoxelHaveCollision(ID voxelID) noexcept;
    [[nodiscard]] bool isVoxelTransparent(ID voxelID) noexcept;
    [[nodiscard]] bool isVoxelOpaque(ID voxelID) noexcept;
    [[nodiscard]] bool isVoxelLightEmitting(ID voxelID) noexcept;
    [[nodiscard]] bool isVoxelAir(ID voxelID) noexcept;
    [[nodiscard]] bool isVoxelLiquid(ID voxelID) noexcept;
    [[nodiscard]] bool isVoxelSolid(ID voxelID) noexcept;
    [[nodiscard]] bool shouldRenderVoxelFace(ID currentVoxel, ID neighborVoxel) noexcept;

    // Fonctions de convenance pour modifier les types de voxels
    void modifyVoxelColor(ID voxelID, const Color& newColor) noexcept;
    void modifyVoxelRenderingMode(ID voxelID, RenderMode newMode) noexcept;
    void modifyVoxelLightLevel(ID voxelID, float newLevel) noexcept;
    void modifyVoxelCollision(ID voxelID, bool hasCollision) noexcept;
    void modifyVoxelName(ID voxelID, std::string_view newName) noexcept;

} // namespace voxel

#endif //PIXLENGINE_VOXEL_TYPE_H