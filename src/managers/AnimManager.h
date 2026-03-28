#pragma once
#include <iostream>
#include <unordered_map>
#include <sstream>
#include "AnimatedSprite.h"
#include "ResourceManager.h"

class AnimManager{
    static std::unordered_map<std::string, AnimatedSprite> animSprites;
public:
    static void trimSpaces(std::string& str);
    static void init(std::string animation_file);
    static void add_anims_from_file(std::string animation_file);
    static void add_anim(std::string name, AnimatedSprite animation);
    static AnimatedSprite get_anim_sprite(std::string name);
    static std::vector<int> get_anim_comp(std::string name);
};
