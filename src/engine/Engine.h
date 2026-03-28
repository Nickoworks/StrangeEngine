#pragma once
#include <iostream>
#include "SDL_include.h"
#include "HardwareInfo.h"
#include "Window.h"
#include "Events.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "HitBoxes.h"
#include "AnimManager.h"
#include "constants.h"
#include "Game.h"
#include "Audio.h"
#include "VFX.h"
#include "ShaderManager.h"

namespace Engine{
    extern std::string version;
    extern std::string assets_path[4];
    extern std::string hitBoxes_path;
    extern std::string signals_path;
    extern std::string animations_path;
    extern std::string audio_config_path;
    extern std::string shaders_path;
    void init(std::string mode);
    void init(void);
    void process(void);
    void clear_mem(void);
    void terminate(void);
}
