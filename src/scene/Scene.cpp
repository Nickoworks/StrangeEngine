#include "Scene.h"

std::string Scene::playerProperties;
std::string Scene::entityManagerCfg;
std::string Scene::objectManagerCfg;
std::string Scene::tileMapCfg;
std::string Scene::script;
std::string Scene::physicsBodiesCfg;

void Scene::trimSpaces(std::string& str) {
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    if(start == std::string::npos){
        str = "";
    } else {
        str = str.substr(start, end - start + 1);
    }
}

void Scene::preload(std::string scene_file_){
    std::istringstream scenefile(scene_file_);
    std::string line;

    bool in_entitySection = false;
    bool in_objectSection = false;
    bool in_physicSection = false;

    while(std::getline(scenefile, line)){
        if(line == ""){
            continue;
        }
        if(line.find("//") != std::string::npos){
            continue;
        }

        size_t player_prop_pos = line.find("PlayerProperties");
        if(player_prop_pos != std::string::npos){
            size_t pos = line.find(":");
            line.erase(0, pos);
            std::istringstream player_line(line);
            
            //int x, int y, int width, int height, Texture* player_texture, SDL_Rect hit_box, bool is_blocked
            std::string x;
            std::string y;
            std::string width;
            std::string height;
            std::string texture_name;
            std::string hitBoxName;
            std::string is_blocked_; 
            std::string script;
            
            std::getline(player_line, x, ',');
            std::getline(player_line, y, ',');
            std::getline(player_line, width, ',');
            std::getline(player_line, height, ',');
            std::getline(player_line, texture_name, ',');
            std::getline(player_line, hitBoxName, ',');
            std::getline(player_line, is_blocked_, ',');
            std::getline(player_line, script, ',');

            trimSpaces(x);
            trimSpaces(y);
            trimSpaces(width);
            trimSpaces(height);
            trimSpaces(texture_name);
            trimSpaces(hitBoxName);
            trimSpaces(is_blocked_);
            trimSpaces(script);
        }

        size_t script_pos = line.find("Script");
        if(script_pos != std::string::npos){
            size_t pos = line.find(":");
            line.erase(0, pos+1);
            trimSpaces(line);
            script = line;
        }

        size_t tilemap_pos = line.find("Tilemap");
        if(tilemap_pos != std::string::npos){
            size_t pos = line.find(":");
            line.erase(0, pos);
            std::istringstream tilemap_line(line);
            //Uint16 id, Texture* tilesheet, int width, int height, int tilesize, int x, int y, double scale
            std::string id;
            std::string texture_name;
            std::string width;
            std::string height;
            std::string tilesize;
            std::string x;
            std::string y;
            std::string scale;

            std::getline(tilemap_line, id, ',');
            std::getline(tilemap_line, texture_name, ',');
            std::getline(tilemap_line, width, ',');
            std::getline(tilemap_line, height, ',');
            std::getline(tilemap_line, tilesize, ',');
            std::getline(tilemap_line, x, ',');
            std::getline(tilemap_line, y, ',');
            std::getline(tilemap_line, scale, ',');

            trimSpaces(id);
            trimSpaces(texture_name);
            trimSpaces(width);
            trimSpaces(height);
            trimSpaces(tilesize);
            trimSpaces(x);
            trimSpaces(y);
            trimSpaces(scale);
        }
        
        size_t entity_container_pos = line.find("[Entity");
        if(entity_container_pos != std::string::npos){
            in_entitySection = true;
            std::getline(scenefile, line);
        }
        if(in_entitySection){
            if(line.find("EntityEnd]") != std::string::npos){
                in_entitySection = false;
                continue;
            }
            if(line.find("//") != std::string::npos){
                continue;
            }
            entityManagerCfg += line + '\n';
            continue;
        }

        size_t object_container_pos = line.find("[Object");
        if(object_container_pos != std::string::npos){
            in_objectSection = true;
            std::getline(scenefile, line);
        }
        if(in_objectSection){
            if(line.find("ObjectEnd]") != std::string::npos){
                in_objectSection = false;
                continue;
            }
            if(line.find("//") != std::string::npos){
                continue;
            }
            objectManagerCfg += line + '\n';
            continue;
        }

        size_t physic_container_pos = line.find("[PhysicBodies");
        if(physic_container_pos != std::string::npos){
            in_physicSection = true;
            std::getline(scenefile, line);
        }
        if(in_physicSection){
            if(line.find("PhysicBodiesEnd]") != std::string::npos){
                in_physicSection = false;
                continue;
            }
            if(line.find("//") != std::string::npos){
                continue;
            }
            physicsBodiesCfg += line + '\n';
            continue;
        }

    }

    Physics::setPhysicsBodiesFromFile(physicsBodiesCfg);
    ObjectManager::changeCfg(objectManagerCfg);
    EntityManager::changeCfg(entityManagerCfg);

    objectManagerCfg = "";
    entityManagerCfg = "";
    physicsBodiesCfg = "";

    LOG("SCENE", "is preloaded!");
}

void Scene::execute(){
    ScriptRegistry::runScript(script);
}
