#include "core/Application.h"
#include "platform/Platform.h"
#include "voxelEngine/ChunkScene.h"
#include "core/Logger.h"

int main() {
    Logger::setLevel(LogLevel::Debug);
    Platform::enableAnsiColors();
    Application& app = Application::get();

    if (!app.initialize()) {
        Logger::error() << "Failed to initialize application";
        return -1;
    }

    app.getSceneManager()->registerScene<ChunkScene>("chunk");
    if (!app.getSceneManager()->loadScene("chunk")) {
        Logger::error() << "Failed to load voxelEngine scene";
        app.shutdown();
        return -1;
    }

    Logger::success() << "Starting voxel Engine...";
    app.run();
    app.shutdown();

    return 0;
}

//TODO: Tchat/Console
//TODO: Schematics