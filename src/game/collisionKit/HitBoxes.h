#pragma once
#include <iostream>
#include "SDL_include.h"
#include <unordered_map>
#include <sstream>
#include "Logger.h"

class HitBoxes{
    static std::unordered_map<std::string, SDL_Rect> RectContainer;
public:
    static void init(std::string rectData);
    static SDL_Rect getHitBox(std::string name);
};
