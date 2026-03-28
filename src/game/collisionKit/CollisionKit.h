#pragma once
#include "SDL_include.h"

struct CollisionKit {
    static bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
};

