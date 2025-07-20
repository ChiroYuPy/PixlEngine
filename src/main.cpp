#include <iostream>
#include "core/Application.h"
#include "platform/Platform.h"
#include "voxelEngine/ChunkScene.h"

int main() {
    Platform::enableAnsiColors();
    Application& app = Application::getInstance();

    if (!app.initialize()) {
        std::cerr << "Failed to initialize application" << std::endl;
        return -1;
    }

    app.getSceneManager()->registerScene<ChunkScene>("chunk");
    if (!app.getSceneManager()->loadScene("chunk")) {
        std::cerr << "Failed to load voxelEngine scene" << std::endl;
        app.shutdown();
        return -1;
    }

    std::cout << "Starting Voxel Engine..." << std::endl;
    app.run();
    app.shutdown();

    return 0;
}