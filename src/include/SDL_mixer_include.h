#pragma once

#ifdef _WIN32
    #include <SDL2/SDL_mixer.h>
#elif __linux__
    #include <SDL2/SDL_mixer.h>
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        #include <SDL2_mixer/SDL_mixer.h>
    #elif TARGET_OS_IOS
        #include "SDL_mixer.h"
    #endif
#else
    #error "Unsupported platform"
#endif