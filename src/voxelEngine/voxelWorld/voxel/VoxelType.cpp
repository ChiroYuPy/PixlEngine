//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/voxelWorld/voxel/VoxelType.h"
#include <algorithm>

namespace voxel {

    // Implémentation du constructeur
    VoxelTypeDefinition::VoxelTypeDefinition(std::string_view displayName,
                                             const Color &color,
                                             RenderMode renderingMode,
                                             bool hasCollision)
            : displayName(displayName),
              color(color),
              renderMode(renderingMode),
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
                false
        };

        registry[DIRT] = VoxelTypeDefinition{
                "Dirt Block",
                Color::fromHex(0x80522F),
                RenderMode::OPAQUE,
                true
        };

        registry[GRASS] = VoxelTypeDefinition{
                "Grass Block",
                Color::fromHex(0x7CAC17),
                RenderMode::OPAQUE,
                true
        };

        registry[STONE] = VoxelTypeDefinition{
                "Stone Block",
                Color::fromHex(0x7F7F7F),
                RenderMode::OPAQUE,
                true
        };

        registry[SAND] = VoxelTypeDefinition{
                "Sand Block",
                Color::fromHex(0xFAF0CF),
                RenderMode::OPAQUE,
                true
        };

        registry[WATER] = VoxelTypeDefinition{
                "Water",
                Color::fromHex(0x3F76E480, true),
                RenderMode::TRANSPARENT,
                false
        };

        registry[LAVA] = VoxelTypeDefinition{
                "Lava",
                Color::fromHex(0xCF4A0F),
                RenderMode::OPAQUE,
                false
        };

        registry[GLASS] = VoxelTypeDefinition{
                "Glass Block",
                Color::fromHex(0xFFFFFF40, true),
                RenderMode::TRANSPARENT,
                true
        };

        registry[WOOD] = VoxelTypeDefinition{
                "Wood Log",
                Color::fromHex(0x6B4F2F),
                RenderMode::OPAQUE,
                true
        };

        registry[LEAVES] = VoxelTypeDefinition{
                "Leaves",
                Color::fromHex(0x4C9B23A0, true),
                RenderMode::TRANSPARENT,
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

    const std::string &getDisplayName(ID voxelID) noexcept {
        return getVoxelTypeDefinition(voxelID).displayName;
    }

    Color getVoxelColor(ID voxelID) noexcept {
        return getVoxelTypeDefinition(voxelID).color;
    }

    RenderMode getRenderMode(ID voxelID) noexcept {
        return getVoxelTypeDefinition(voxelID).renderMode;
    }

    bool doesVoxelHaveCollision(ID voxelID) noexcept {
        return getVoxelTypeDefinition(voxelID).hasCollision;
    }

    bool isVoxelTransparent(ID voxelID) noexcept {
        RenderMode mode = getRenderMode(voxelID);
        return mode == RenderMode::TRANSPARENT;
    }

    bool isVoxelOpaque(ID voxelID) noexcept {
        RenderMode mode = getRenderMode(voxelID);
        return mode == RenderMode::OPAQUE;
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
}