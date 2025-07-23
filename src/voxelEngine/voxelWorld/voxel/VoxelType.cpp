//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/voxelWorld/voxel/VoxelType.h"
#include <algorithm>

namespace voxel {

    // Implémentation du constructeur
    VoxelTypeDefinition::VoxelTypeDefinition(std::string_view displayName, const Color &color,
                                             RenderMode renderingMode, float lightEmissionLevel,
                                             bool hasCollision)
            : displayName(displayName),
              color(color),
              renderMode(renderingMode),
              lightEmissionLevel(lightEmissionLevel),
              hasCollision(hasCollision) {}

    // Implémentation du singleton
    VoxelTypeRegistry* VoxelTypeRegistry::instance = nullptr;

    VoxelTypeRegistry::VoxelTypeRegistry() {
        // Initialisation des valeurs par défaut
        resetToDefaults();
    }

    VoxelTypeRegistry& VoxelTypeRegistry::getInstance() {
        if (instance == nullptr) {
            instance = new VoxelTypeRegistry();
        }
        return *instance;
    }

    const VoxelTypeDefinition& VoxelTypeRegistry::getDefinition(ID voxelID) const noexcept {
        return registry[voxelID];
    }

    void VoxelTypeRegistry::setDefinition(ID voxelID, const VoxelTypeDefinition& definition) noexcept {
        if (isValidVoxelID(voxelID)) {
            registry[voxelID] = definition;
        }
    }

    void VoxelTypeRegistry::setColor(ID voxelID, const Color& color) noexcept {
        if (isValidVoxelID(voxelID)) {
            registry[voxelID].color = color;
        }
    }

    void VoxelTypeRegistry::setRenderingMode(ID voxelID, RenderMode mode) noexcept {
        if (isValidVoxelID(voxelID)) {
            registry[voxelID].renderMode = mode;
        }
    }

    void VoxelTypeRegistry::setLightEmissionLevel(ID voxelID, float level) noexcept {
        if (isValidVoxelID(voxelID)) {
            registry[voxelID].lightEmissionLevel = std::clamp(level, 0.0f, 1.0f);
        }
    }

    void VoxelTypeRegistry::setCollision(ID voxelID, bool hasCollision) noexcept {
        if (isValidVoxelID(voxelID)) {
            registry[voxelID].hasCollision = hasCollision;
        }
    }

    void VoxelTypeRegistry::setDisplayName(ID voxelID, std::string_view name) noexcept {
        if (isValidVoxelID(voxelID)) {
            registry[voxelID].displayName = name;
        }
    }

    void VoxelTypeRegistry::resetToDefaults() noexcept {
        // Réinitialiser tous les types à "Unknown Block" par défaut
        for (auto& def : registry) {
            def = VoxelTypeDefinition{};
        }

        // Définir les types de base
        registry[AIR] = VoxelTypeDefinition{
                "Air",
                Color::fromHex(0x000000),
                RenderMode::INVISIBLE,
                0.0f,
                false
        };

        registry[DIRT] = VoxelTypeDefinition{
                "Dirt Block",
                Color::fromHex(0x80522F),
                RenderMode::OPAQUE,
                0.0f,
                true
        };

        registry[GRASS] = VoxelTypeDefinition{
                "Grass Block",
                Color::fromHex(0x7CAC17),
                RenderMode::OPAQUE,
                0.0f,
                true
        };

        registry[STONE] = VoxelTypeDefinition{
                "Stone Block",
                Color::fromHex(0x7F7F7F),
                RenderMode::OPAQUE,
                0.0f,
                true
        };

        registry[SAND] = VoxelTypeDefinition{
                "Sand Block",
                Color::fromHex(0xFAF0CF),
                RenderMode::OPAQUE,
                0.0f,
                true
        };

        registry[WATER] = VoxelTypeDefinition{
                "Water",
                Color::fromHex(0x3F76E480, true),
                RenderMode::TRANSPARENT,
                0.0f,
                false
        };

        registry[LAVA] = VoxelTypeDefinition{
                "Lava",
                Color::fromHex(0xCF4A0F),
                RenderMode::EMISSIVE,
                0.9f,
                false
        };

        registry[GLASS] = VoxelTypeDefinition{
                "Glass Block",
                Color::fromHex(0xFFFFFF40, true),
                RenderMode::TRANSPARENT,
                0.0f,
                true
        };

        registry[WOOD] = VoxelTypeDefinition{
                "Wood Log",
                Color::fromHex(0x6B4F2F),
                RenderMode::OPAQUE,
                0.0f,
                true
        };

        registry[LEAVES] = VoxelTypeDefinition{
                "Leaves",
                Color::fromHex(0x4C9B23A0, true),
                RenderMode::TRANSPARENT,
                0.0f,
                true
        };
    }

    // Fonctions utilitaires (inchangées)
    bool isValidVoxelID(ID voxelID) noexcept {
        return voxelID <= MAX_TYPE_ID;
    }

    const VoxelTypeDefinition &getVoxelTypeDefinition(ID voxelID) noexcept {
        return VoxelTypeRegistry::getInstance().getDefinition(voxelID);
    }

    const std::string &getVoxelDisplayName(ID voxelID) noexcept {
        return getVoxelTypeDefinition(voxelID).displayName;
    }

    Color getVoxelColor(ID voxelID) noexcept {
        return getVoxelTypeDefinition(voxelID).color;
    }

    RenderMode getRenderMode(ID voxelID) noexcept {
        return getVoxelTypeDefinition(voxelID).renderMode;
    }

    float getVoxelLightEmissionLevel(ID voxelID) noexcept {
        return getVoxelTypeDefinition(voxelID).lightEmissionLevel;
    }

    bool doesVoxelHaveCollision(ID voxelID) noexcept {
        return getVoxelTypeDefinition(voxelID).hasCollision;
    }

    bool isVoxelTransparent(ID voxelID) noexcept {
        RenderMode mode = getRenderMode(voxelID);
        return mode == RenderMode::TRANSPARENT || mode == RenderMode::INVISIBLE;
    }

    bool isVoxelOpaque(ID voxelID) noexcept {
        RenderMode mode = getRenderMode(voxelID);
        return mode == RenderMode::OPAQUE || mode == RenderMode::EMISSIVE;
    }

    bool isVoxelLightEmitting(ID voxelID) noexcept {
        return getRenderMode(voxelID) == RenderMode::EMISSIVE;
    }

    bool isVoxelAir(ID voxelID) noexcept {
        return voxelID == AIR;
    }

    bool isVoxelLiquid(ID voxelID) noexcept {
        return voxelID == WATER || voxelID == LAVA;
    }

    bool isVoxelSolid(ID voxelID) noexcept {
        return !isVoxelAir(voxelID) && !isVoxelLiquid(voxelID);
    }

    bool shouldRenderVoxelFace(ID currentVoxel, ID neighborVoxel) noexcept {
        if (currentVoxel == AIR) return false;
        if (neighborVoxel == AIR) return true;

        // Si les deux voxels sont opaques, pas besoin de rendre la face
        if (isVoxelOpaque(currentVoxel) && isVoxelOpaque(neighborVoxel)) {
            return false;
        }

        // Cas spéciaux pour l'eau et autres liquides
        if (currentVoxel == neighborVoxel && isVoxelLiquid(currentVoxel)) {
            return false; // Pas de faces entre blocs identiques liquides
        }

        return true;
    }

    // Fonctions de convenance pour modifier les types
    void modifyVoxelColor(ID voxelID, const Color& newColor) noexcept {
        VoxelTypeRegistry::getInstance().setColor(voxelID, newColor);
    }

    void modifyVoxelRenderingMode(ID voxelID, RenderMode newMode) noexcept {
        VoxelTypeRegistry::getInstance().setRenderingMode(voxelID, newMode);
    }

    void modifyVoxelLightLevel(ID voxelID, float newLevel) noexcept {
        VoxelTypeRegistry::getInstance().setLightEmissionLevel(voxelID, newLevel);
    }

    void modifyVoxelCollision(ID voxelID, bool hasCollision) noexcept {
        VoxelTypeRegistry::getInstance().setCollision(voxelID, hasCollision);
    }

    void modifyVoxelName(ID voxelID, std::string_view newName) noexcept {
        VoxelTypeRegistry::getInstance().setDisplayName(voxelID, newName);
    }

}