#include "HitBoxes.h"

std::unordered_map<std::string, SDL_Rect> HitBoxes::RectContainer;

void HitBoxes::init(std::string rectData){
    std::istringstream hitBoxCfgFile(rectData);
    std::string line;

    while(std::getline(hitBoxCfgFile, line)){
        size_t pos = line.find(":");
        std::string name = line.substr(0, pos);
        std::string x;
        std::string y;
        std::string w;
        std::string h;
        line.erase(0, pos+1);
        std::istringstream params(line);
        
        std::getline(params, x, ',');
        std::getline(params, y, ',');
        std::getline(params, w, ',');
        std::getline(params, h, ',');

        RectContainer[name] = {std::stoi(x), std::stoi(y), std::stoi(w), std::stoi(h)};
    }
}

SDL_Rect HitBoxes::getHitBox(std::string name){
    auto it = RectContainer.find(name);
    if(it != RectContainer.end()){
        return it->second;
    } else {
        LOG("HITBOXES WARNING", "HitBox not found " + name, YELLOW_CODE);
        throw std::invalid_argument("HitBox is not found");
    }
}
