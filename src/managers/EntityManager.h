#pragma once
#include <iostream>
#include <unordered_map>
#include "Texture.h"
#include "Entity.h"
#include "Preloader.h"
#include "HitBoxes.h"
#include "ResourceManager.h"
#include "Logger.h"
#include "Physics.h"

#include <memory>
#include <sstream>

class EntityManager{
    static bool is_blocked;
    static bool visible;
    static std::string width;
    static std::string height;
    static std::string x;
    static std::string y;
    static std::string static_frame_ID;
    static std::string is_blocked_;
    static std::string texture_name;
    static std::string hitBoxName;
    static std::string script;
    static std::string physic_body_name;
    static std::string physic_body_layer;
    static std::string visible_;

    static std::unordered_map<std::string, Entity> EntityContainer;
    static void trimSpaces(std::string& str);
    static void _readCfgLine(std::string line, size_t pos);
    static void _createEntities(std::string cfg);
public:
    static void changeCfg(std::string cfg);
    static Entity* getEntity(std::string name);
};
