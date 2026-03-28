#pragma once

#ifdef _WIN32
    #include <SDL2/SDL_ttf.h>
#elif __linux__
    #include <SDL2/SDL_ttf.h>
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        #include <SDL2_ttf/SDL_ttf.h>
    #elif TARGET_OS_IOS
        #include "SDL_ttf.h"
    #endif
#else
    #error "Unsupported platform"
#endif