#pragma once
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include "Texture.h"
#include "Object.h"
#include "Preloader.h"
#include "HitBoxes.h"
#include "ResourceManager.h"
#include "ScriptRegistry.h"
#include "Logger.h"

//int x, int y, int width, int height, int static_frame_ID, bool is_blocked, Texture* texture, SDL_Rect hit_box

class ObjectManager{     
    static bool is_blocked;
    static bool visible;
    static std::string x;
    static std::string y;
    static std::string width;
    static std::string height;
    static std::string static_frame_ID;
    static std::string texture_name;
    static std::string hitBoxName;
    static std::string is_blocked_;
    static std::string script;
    static std::string visible_;
    
    static std::string physic_body_type;
    static std::string physic_body_layer;
    static std::string physic_body_name;

    static std::unordered_map<std::string, Object> ObjectContainer;
    static void trimSpaces(std::string& str);
    static void _readCfgLine(std::string line, size_t pos);
    static void _createObjects(std::string cfg);
    static bool _checkToValidValues();
public:
    static void changeCfg(std::string cfg);
    static Object* getObject(std::string name);
    static std::vector<std::string> getObjectsNames();
};
