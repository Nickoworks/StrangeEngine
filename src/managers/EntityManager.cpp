#include "EntityManager.h"


bool EntityManager::is_blocked = false;
bool EntityManager::visible = true;
std::string EntityManager::width;
std::string EntityManager::height;
std::string EntityManager::x;
std::string EntityManager::y;
std::string EntityManager::static_frame_ID;
std::string EntityManager::is_blocked_;
std::string EntityManager::texture_name;
std::string EntityManager::hitBoxName;
std::string EntityManager::script;
std::string EntityManager::physic_body_name;
std::string EntityManager::physic_body_layer;
std::string EntityManager::visible_;

std::unordered_map<std::string, Entity> EntityManager::EntityContainer;

void EntityManager::trimSpaces(std::string& str) {
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    if(start == std::string::npos){
        str = "";
    } else {
        str = str.substr(start, end - start + 1);
    }
}

void EntityManager::_readCfgLine(std::string line, size_t pos){
    std::string line_ = line;
    line_.erase(0, pos+1);
    std::istringstream params(line_);
    std::getline(params, width, ',');
    std::getline(params, height, ',');
    std::getline(params, x, ',');
    std::getline(params, y, ',');
    std::getline(params, static_frame_ID, ',');
    std::getline(params, is_blocked_, ',');
    std::getline(params, texture_name, ',');
    std::getline(params, hitBoxName, ',');
    std::getline(params, script, ',');
    std::getline(params, physic_body_name, ',');
    std::getline(params, physic_body_layer, ',');
    std::getline(params, visible_, ',');

    trimSpaces(width);
    trimSpaces(height);
    trimSpaces(x);
    trimSpaces(y);
    trimSpaces(static_frame_ID);
    trimSpaces(is_blocked_);
    trimSpaces(texture_name);
    trimSpaces(hitBoxName);
    trimSpaces(script);
    trimSpaces(physic_body_name);
    trimSpaces(physic_body_layer);
    trimSpaces(visible_);
    if(is_blocked_ == "true"){
        is_blocked = true;
    } else if(is_blocked_ == "false"){
        is_blocked = false;
    } else {
        LOG("ERROR", "undefined value for is_blocked " + is_blocked_);
    }
    if(visible_ == "true"){
        visible = true;
    } else if(visible_ == "false"){
        visible = false;
    } else {
        LOG("ERROR", "undefined value for visible " + visible_);
    }
}

void EntityManager::_createEntities(std::string cfg){
    std::istringstream cfgFile(cfg);
    std::string line;

    while(std::getline(cfgFile, line)){
        if(line == ""){
            continue;
        }
        size_t pos = line.find(":");
        std::string name = line.substr(0, pos);
        trimSpaces(name);
        _readCfgLine(line, pos);

        EntityContainer.emplace(name, Entity(
            std::stoi(width),
            std::stoi(height),
            std::stoi(x),
            std::stoi(y),
            std::stoi(static_frame_ID),
            is_blocked,
            ResourceManager::getTexture(texture_name),
            HitBoxes::getHitBox(hitBoxName),
            script,
            Physics::getKinematicBody(std::stoi(physic_body_layer), physic_body_name),
            visible   
        ));
        LOG("ENTITY MANAGER", "entity is created " + name);
    }   
}

void EntityManager::changeCfg(std::string cfg){
    EntityContainer.clear();
    _createEntities(cfg);
    LOG("ENTITY MANAGER", "is changed cfg!");
}

Entity* EntityManager::getEntity(std::string name){
    auto it = EntityContainer.find(name);

    if(it != EntityContainer.end()){
        return &it->second;
    }
    LOG("ENTITY MANAGER WARNING", "entity " + name + " not found in current scene!", YELLOW_CODE);
    return nullptr;
}
