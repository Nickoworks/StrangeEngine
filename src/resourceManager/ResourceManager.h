#pragma once
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include "Texture.h"
#include "Preloader.h"
#include "Logger.h"
#include "SDL_include.h"

#include "SDL_ttf_include.h"
#include "SDL_mixer_include.h"

#include <memory>
#include <sstream>

enum ResourceKind{
    TEXTURES_DIR = 0,
    AUDIO_DIR = 1,
    MAP_DIR = 2,
    FONT_DIR = 3
};

struct TextureData{
    int width;
    int height;
    float scale;
};

class ResourceManager{
    std::string TexturesDir;
    std::string AudioDir;
    std::string MapDir;
    std::string FontsDir;

public:
    static std::unordered_map<std::string, std::unique_ptr<Texture> > TextureContainer;
    static std::unordered_map<std::string, Mix_Chunk*> AudioContainer;
    static std::unordered_map<std::string, std::string> MapContainer;
    static std::unordered_map<std::string, TTF_Font*> FontsContainer;


    using TextureMap = std::unordered_map<std::string, TextureData>;
    using FontMap = std::unordered_map<std::string, int>;

    static void trimSpaces(std::string& str);
    static TextureMap parseTextureProp(std::string data);
    static FontMap parseFontProp(std::string data);
    static void init(std::string paths[4]);
    static void clear();
    static Texture* getTexture(std::string name);
    static std::string getMap(std::string id);
    static TTF_Font* getFont(std::string name);
    static Mix_Chunk* getAudio(std::string name);
    static std::string readFile(std::string path);
    static void saveFile(std::string text, std::string path);
};
