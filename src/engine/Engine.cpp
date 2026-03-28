#include "Engine.h"

#if defined(__APPLE__) || defined (__linux__)
    std::string Engine::assets_path[4] = {"../res/textures.dat", 
                                            "../res/audio.dat", 
                                            "../res/map.dat", 
                                            "../res/fonts.dat"};
    std::string Engine::hitBoxes_path = "../res/data.dat/hitboxes.dat";
    std::string Engine::signals_path = "../res/data.dat/signals.dat";
    std::string Engine::animations_path = "../res/data.dat/animations.dat";
    std::string Engine::audio_config_path = "../res/data.dat/audio_channels.dat";
    std::string Engine::shaders_path = "../res/shaders.dat";
#elif defined(_WIN32)
    std::string Engine::assets_path[4] = {"..\\res\\textures.dat", 
                            "..\\res\\audio.dat", 
                            "..\\res\\map.dat", 
                            "..\\res\\fonts.dat"};
    std::string Engine::hitBoxes_path = "..\\res\\data.dat\\hitboxes.dat";
    std::string Engine::signals_path = "..\\res\\data.dat\\signals.dat";
    std::string Engine::animations_path = "..\\res\\data.dat\\animations.dat";
    std::string Engine::audio_config_path = "..\\res\\data.dat\\audio_channels.dat";
    std::string Engine::shaders_path = "..\\res\\shaders.dat";
#endif

std::string Engine::version = ENGINE_VERSION;

void Engine::init(std::string mode){
    SDL_version currentVersion;
    SDL_GetVersion(&currentVersion);
    std::ostringstream oss;
    oss << "ENGINE IS STARTING " << "(SDL " << static_cast<int>(currentVersion.major) << '.' 
    << static_cast<int>(currentVersion.minor) << '.' << static_cast<int>(currentVersion.patch) << ')';

    LOG("INFO", oss.str());
    LOG("INFO", "ENGINE VERSION " + version);

    getCpuInfo();
    getMemoryInfo();

    if(mode == "editor"){
        Window::initialise(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
        Renderer::initialise(Window::getWindow(), VIDEO_ADAPTER_INDEX, VSYNC, "editor");
    } else {
        Window::initialise(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
        Renderer::initialise(Window::getWindow(), VIDEO_ADAPTER_INDEX, VSYNC);
    }
    Events::initialise(signals_path);

    // textures, music, maps, fonts
    Audio::init(Preloader::load_file(audio_config_path));
    HitBoxes::init(Preloader::load_file(hitBoxes_path));
    ResourceManager::init(assets_path);
    AnimManager::init(Preloader::load_file(animations_path));
    ShaderManager::init(shaders_path);  
    VFX::init();
}

void Engine::init(void){
    SDL_version currentVersion;
    SDL_GetVersion(&currentVersion);
    std::ostringstream oss;
    oss << "ENGINE IS STARTING " << "(SDL " << static_cast<int>(currentVersion.major) << '.' 
    << static_cast<int>(currentVersion.minor) << '.' << static_cast<int>(currentVersion.patch) << ')';

    LOG("INFO", oss.str());

    getCpuInfo();
    getMemoryInfo();

    Window::initialise(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    Renderer::initialise(Window::getWindow(), VIDEO_ADAPTER_INDEX, VSYNC);
    Events::initialise(signals_path);

    // textures, music, maps, fonts
    Audio::init(Preloader::load_file(audio_config_path));
    HitBoxes::init(Preloader::load_file(hitBoxes_path));
    ResourceManager::init(assets_path);
    AnimManager::init(Preloader::load_file(animations_path));
    ShaderManager::init(shaders_path);
    VFX::init();
}

void Engine::process(void){
    Game game;
    game.game_loop();
    terminate();
}

void Engine::clear_mem(void){
    ResourceManager::clear();
    Audio::close_audio();
    Renderer::destroy();
    VFX::delete_buffers();
    ShaderManager::deleteAllShaders();
    Window::destroy();
    LOG("INFO", "MEMORY IS FREE");
}

void Engine::terminate(void){
    clear_mem();
    LOG("INFO", "ENGINE SHUTTING DOWN");
    Window::terminate();
}
