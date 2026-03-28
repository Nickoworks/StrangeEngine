#pragma once
#include <iostream>
#include <unordered_map>
#include <sstream>
#include "Preloader.h"
#include "Renderer.h"
#include "ScriptRegistry.h"
#include "EntityManager.h"
#include "ObjectManager.h"
#include "Physics.h"
#include "Logger.h"
class Scene{
    static std::string playerProperties;
    static std::string entityManagerCfg;
    static std::string objectManagerCfg;
    static std::string physicsBodiesCfg;
    static std::string tileMapCfg;
    static std::string script;
    static void trimSpaces(std::string& str);
public:
    static void preload(std::string scene_file_);
    static void render();
    static void execute();
};
