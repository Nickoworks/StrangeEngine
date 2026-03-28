#pragma once

#ifdef _WIN32
    #include <SDL2/SDL_image.h>
#elif __linux__
    #include <SDL2/SDL_image.h>
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        #include <SDL2_image/SDL_image.h>
    #elif TARGET_OS_IOS
        #include "SDL_image.h"
    #endif
#else
    #error "Unsupported platform"
#endif