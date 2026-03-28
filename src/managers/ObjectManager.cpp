#include "ObjectManager.h"

bool ObjectManager::is_blocked = false;
bool ObjectManager::visible = true;
std::string ObjectManager::width;
std::string ObjectManager::height;
std::string ObjectManager::x;
std::string ObjectManager::y;
std::string ObjectManager::static_frame_ID;
std::string ObjectManager::is_blocked_;
std::string ObjectManager::texture_name;
std::string ObjectManager::hitBoxName;
std::string ObjectManager::script;
std::string ObjectManager::visible_;

std::string ObjectManager::physic_body_type;
std::string ObjectManager::physic_body_layer;
std::string ObjectManager::physic_body_name;

std::unordered_map<std::string, Object> ObjectManager::ObjectContainer;

void ObjectManager::trimSpaces(std::string& str){
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    if(start == std::string::npos){
        str = "";
    } else {
        str = str.substr(start, end - start + 1);
    }
}

void ObjectManager::_readCfgLine(std::string line, size_t pos){
    std::string line_ = line;
    line_.erase(0, pos+1);

    std::string notformattedPhysicBody;

    std::istringstream params(line_);
    std::getline(params, x, ',');
    std::getline(params, y, ',');
    std::getline(params, width, ',');
    std::getline(params, height, ',');
    std::getline(params, static_frame_ID, ',');
    std::getline(params, is_blocked_, ',');
    std::getline(params, texture_name, ',');
    std::getline(params, hitBoxName, ',');
    std::getline(params, script, ',');
    std::getline(params, notformattedPhysicBody, ',');
    std::getline(params, physic_body_layer, ',');
    std::getline(params, visible_, ',');

    trimSpaces(notformattedPhysicBody);
    trimSpaces(physic_body_layer);
    trimSpaces(width);
    trimSpaces(height);
    trimSpaces(x);
    trimSpaces(y);
    trimSpaces(static_frame_ID);
    trimSpaces(is_blocked_);
    trimSpaces(texture_name);
    trimSpaces(hitBoxName);
    trimSpaces(script);
    trimSpaces(visible_);

    size_t pos_ = notformattedPhysicBody.find("-");

    physic_body_type = notformattedPhysicBody.substr(0, pos_);
    physic_body_name = notformattedPhysicBody.substr(pos_+1, notformattedPhysicBody.length());

    if(is_blocked_ == "true"){
        is_blocked = true;
    } else if(is_blocked_ == "false"){
        is_blocked = false;
    }
    if(visible_ == "true"){
        visible = true;
    } else if(visible_ == "false"){
        visible = false;
    }
}

bool _checkToValidIntValue(std::string x){
    try{
        std::stoi(x);
        return true;
    } catch (const std::invalid_argument& e) {
        return false;
    } catch(const std::out_of_range& e) {
        return false;
    }
}   

bool ObjectManager::_checkToValidValues(){
    if(!_checkToValidIntValue(x) || !_checkToValidIntValue(y) ||
    !_checkToValidIntValue(width) || !_checkToValidIntValue(height) || 
    !_checkToValidIntValue(static_frame_ID)){
        return false;
    }
    if(is_blocked_ != "true" && is_blocked_ != "false"){
        LOG("DEBUG", is_blocked_);
        return false;
    }
    if(ResourceManager::getTexture(texture_name) == nullptr){
        return false;
    }
    try{
        HitBoxes::getHitBox(hitBoxName);
    } catch(const std::invalid_argument& e){
        return false;
    }
    if(script == "NULL" || script == "null"){
        return true;
    }
    if(!ScriptRegistry::isValidScript(script)){
        return false;
    }
    return true;
}

void ObjectManager::_createObjects(std::string cfg){
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

        if(!_checkToValidValues()){
            LOG("OBJECT MANAGER ERROR", "invalid arguments for create object " + name, WHITE_RED_CODE);
            continue;
        }
        //int x, int y, int width, int height, int static_frame_ID, bool is_blocked, Texture* texture, SDL_Rect hit_box

        if(physic_body_type == "StaticBody"){
            ObjectContainer.emplace(name, Object(
                std::stoi(x),
                std::stoi(y),
                std::stoi(width),
                std::stoi(height),
                std::stoi(static_frame_ID),
                is_blocked,
                ResourceManager::getTexture(texture_name),
                HitBoxes::getHitBox(hitBoxName),
                script,
                Physics::getStaticBody(std::stoi(physic_body_layer), physic_body_name),
                visible
            ));
        }
        else if(physic_body_type == "RigidBody"){
            ObjectContainer.emplace(name, Object(
                std::stoi(x),
                std::stoi(y),
                std::stoi(width),
                std::stoi(height),
                std::stoi(static_frame_ID),
                is_blocked,
                ResourceManager::getTexture(texture_name),
                HitBoxes::getHitBox(hitBoxName),
                script,
                Physics::getRigidBody(std::stoi(physic_body_layer), physic_body_name),
                visible
            ));
        }
        
        LOG("OBJECT MANAGER", "object is created " + name);
    }
}

void ObjectManager::changeCfg(std::string cfg){
    ObjectContainer.clear();
    _createObjects(cfg);
    LOG("OBJECT MANAGER", "is changed cfg!");
}

Object* ObjectManager::getObject(std::string name){
    auto it = ObjectContainer.find(name);

    if(it != ObjectContainer.end()){
        return &it->second;
    }
    return nullptr;
}

std::vector<std::string> ObjectManager::getObjectsNames(){
    std::vector<std::string> arr = {};
    for(auto pair : ObjectContainer){
        arr.push_back(pair.first);
    }
    return arr;
}
