#include "AnimManager.h"

std::unordered_map<std::string, AnimatedSprite> AnimManager::animSprites; 

void AnimManager::trimSpaces(std::string& str) {
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    if(start == std::string::npos){
        str = "";
    } else {
        str = str.substr(start, end - start + 1);
    }
}

void AnimManager::init(std::string animation_file){
    std::istringstream anim_file(animation_file);
    std::string line;

    while(std::getline(anim_file, line)){
        if(line == ""){
            continue;
        }
        size_t pos = line.find(":");
        std::string anim_name = line.substr(0, pos);
        line.erase(0, pos+1);
        trimSpaces(anim_name);
        std::vector<int> anim_comp;
        std::string texture_name;
        std::string frame_width;
        std::string frame_height;

        std::string anim_frames;
        std::string start_anim_frame;
        std::string frame_per_milsec;
        std::string curr_frame;
        std::string frame_last_change;

        std::istringstream params(line);
        std::getline(params, anim_frames, ',');
        std::getline(params, start_anim_frame, ',');
        std::getline(params, frame_per_milsec, ',');
        std::getline(params, curr_frame, ',');
        std::getline(params, frame_last_change, ',');

        std::getline(params, frame_width, ',');
        std::getline(params, frame_height, ',');
        std::getline(params, texture_name, ',');

        trimSpaces(texture_name);
        trimSpaces(frame_width);
        trimSpaces(frame_height);

        trimSpaces(anim_frames);
        trimSpaces(start_anim_frame);
        trimSpaces(frame_per_milsec);
        trimSpaces(curr_frame);
        trimSpaces(frame_last_change);
        try{
            anim_comp.push_back(std::stoi(anim_frames));
            anim_comp.push_back(std::stoi(start_anim_frame));
            anim_comp.push_back(std::stoi(frame_per_milsec));
            anim_comp.push_back(std::stoi(curr_frame));
            anim_comp.push_back(std::stoi(frame_last_change));

            if(texture_name == "null" || texture_name == "NULL"){
                animSprites.emplace(anim_name, AnimatedSprite(
                    anim_comp,
                    std::stoi(frame_width),
                    std::stoi(frame_height),
                    nullptr,
                    true
                ));
            } else {
                animSprites.emplace(anim_name, AnimatedSprite(
                    anim_comp,
                    std::stoi(frame_width),
                    std::stoi(frame_height),
                    ResourceManager::getTexture(texture_name),
                    true
                ));
            }
        } catch(const std::invalid_argument& e) {
            LOG("ANIM MANAGER", "invalid arguments in animation", WHITE_RED_CODE);
        }
    }
}

void AnimManager::add_anims_from_file(std::string animation_file){
    // now this dosen't need
}

void AnimManager::add_anim(std::string name, AnimatedSprite animation){
    animSprites.emplace(name, animation);
}

AnimatedSprite AnimManager::get_anim_sprite(std::string name){
    auto it = animSprites.find(name);
    if(it != animSprites.end()){
        return it->second;
    } else {
        LOG("ANIMATION MANAGER WARNING", "animation " + name + " not found", YELLOW_CODE);
        return AnimatedSprite({0, 0, 0, 0, 0}, 0, 0, nullptr, true);
    }
}

std::vector<int> AnimManager::get_anim_comp(std::string name){
    auto it = animSprites.find(name);
    if(it != animSprites.end()){
        return it->second.get_anim_comp();
    } else {
        LOG("ANIMATION MANAGER WARNING", "animation " + name + " not found", YELLOW_CODE);
        return { };
    }
}
