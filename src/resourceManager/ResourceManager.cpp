#include "ResourceManager.h"

std::unordered_map<std::string, std::unique_ptr<Texture> > ResourceManager::TextureContainer;
std::unordered_map<std::string, Mix_Chunk*> ResourceManager::AudioContainer;
std::unordered_map<std::string, std::string> ResourceManager::MapContainer;
std::unordered_map<std::string, TTF_Font*> ResourceManager::FontsContainer;


void ResourceManager::trimSpaces(std::string& str) {
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    if(start == std::string::npos){
        str = "";
    } else {
        str = str.substr(start, end - start + 1);
    }
}

using TextureMap = std::unordered_map<std::string, TextureData>;
using FontMap = std::unordered_map<std::string, int>;

TextureMap ResourceManager::parseTextureProp(std::string data){
    TextureMap textureMap;
    std::istringstream texture_file(data);
    std::string line;

    while(std::getline(texture_file, line)){
        if(line == ""){
            continue;
        }
        std::string width;
        std::string height;
        std::string scale;

        size_t separator = line.find(":");
        std::string texName = line.substr(0, separator);
        trimSpaces(texName);
        line.erase(0, separator+1);
        std::istringstream sepData(line);
        std::string sub_str;

        std::getline(sepData, width, ',');
        std::getline(sepData, height, ',');
        std::getline(sepData, scale, ',');

        trimSpaces(width);
        trimSpaces(height);
        trimSpaces(scale);

        textureMap[texName] = {std::stoi(width), std::stoi(height), std::stof(scale)};
    }
    return textureMap;
}

FontMap ResourceManager::parseFontProp(std::string data){
    FontMap fontMap;
    std::istringstream font_file(data);
    std::string line;

    while(std::getline(font_file, line)){
        if(line == ""){
            continue;
        }
        size_t separator = line.find(":");
        std::string fontName = line.substr(0, separator);
        trimSpaces(fontName);
        line.erase(0, separator+1);
        trimSpaces(line);

        fontMap[fontName] = std::stoi(line);
    }
    return fontMap;
}



#ifdef __linux__ || _WIN32
void ResourceManager::init(std::string paths[4]){
    std::string texture_prop_file = Preloader::load_file(paths[TEXTURES_DIR] + "/Texture_properties");
    std::string font_prop_file = Preloader::load_file(paths[FONT_DIR] + "/Font_properties");
    TextureMap textureMap = parseTextureProp(texture_prop_file);
    FontMap fontMap = parseFontProp(font_prop_file);
    try{
        for(size_t i = 0; i < 4; i++){
            for(const auto& entry_file : std::filesystem::directory_iterator(paths[i])){
                std::unique_ptr<Texture> texture = nullptr;
                Mix_Chunk* audio = nullptr;
                std::string map = "";
                TTF_Font* font = nullptr;
                std::filesystem::path filePath(entry_file.path());
                
                switch (i){
                    case TEXTURES_DIR:
                        if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "Texture_properties")){
                            texture = Preloader::load_texture(entry_file.path().string(), textureMap[filePath.filename().string()].width, 
                                                                textureMap[filePath.filename().string()].height, textureMap[filePath.filename().string()].scale);
                        }
                        if(texture != nullptr){
                            TextureContainer[filePath.filename().string()] = std::move(texture);
                        } else if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "Texture_properties")) {
                            LOG("WARNING", "texture is not loaded " + entry_file.path().string());
                        }
                        break;
                    case AUDIO_DIR:
                        if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "properties")){
                            audio = Preloader::load_audio(entry_file.path().string());
                        }
                        if(audio != nullptr){
                            AudioContainer[filePath.filename().string()] = audio;
                        }
                        break;
                    case MAP_DIR:
                        if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "properties")){
                            map = Preloader::load_file(entry_file.path().string());
                        }
                        if(map != ""){
                            MapContainer[filePath.filename().string()] = map;
                        } else if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "properties")) {
                            LOG("WARNING", "map is not loaded " + entry_file.path().string());
                        }
                        break;
                    case FONT_DIR:
                        if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "Font_properties")){
                            font = Preloader::load_font(entry_file.path().string(), fontMap[filePath.filename().string()]);
                        }
                        if(font != nullptr){
                            FontsContainer[filePath.filename().string()] = font;
                        } else if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "Font_properties")) {
                            LOG("WARNING", "font is not loaded " + entry_file.path().string());
                        }
                        break;

                    default:
                        break;
                }
            }
            /*LOGGER*/
            switch (i){
                case TEXTURES_DIR:
                    LOG("RESOURCE MANAGER", "texture is loaded!");
                    break;
                case AUDIO_DIR:
                    LOG("RESOURCE MANAGER", "audio is loaded!");
                    break;
                case MAP_DIR:
                    LOG("RESOURCE MANAGER", "maps is loaded!");
                    break;
                case FONT_DIR:
                    LOG("RESOURCE MANAGER", "fonts is loaded!");
                    break;
            
                default:
                    LOG("RESOURCE MANAGER", "error type");
                    break;
            }
        }
    } catch (const std::filesystem::filesystem_error& e){
        LOG("RESOURCE MANAGER ERROR", "filesystem error!", WHITE_RED_CODE);
        LOG("FATAL ERROR", e.what());
    }
    
    LOG("RESOURCE MANAGER", "all assets is preloaded!");
}

#elif __APPLE__
    #include <TargetConditionals.h>

        #if TARGET_OS_IOS

        #endif
#endif

#ifdef __APPLE__
    #include <TargetConditionals.h>

    #if !TARGET_OS_IOS
    void ResourceManager::init(std::string paths[4]){
        std::string texture_prop_file = Preloader::load_file(paths[TEXTURES_DIR] + "/Texture_properties");
        std::string font_prop_file = Preloader::load_file(paths[FONT_DIR] + "/Font_properties");
        TextureMap textureMap = parseTextureProp(texture_prop_file);
        FontMap fontMap = parseFontProp(font_prop_file);
        try{
            for(size_t i = 0; i < 4; i++){
                for(const auto& entry_file : std::filesystem::directory_iterator(paths[i])){
                    std::unique_ptr<Texture> texture = nullptr;
                    Mix_Chunk* audio = nullptr;
                    std::string map = "";
                    TTF_Font* font = nullptr;
                    std::filesystem::path filePath(entry_file.path());
                    
                    switch (i){
                        case TEXTURES_DIR:
                            if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "Texture_properties")){
                                texture = Preloader::load_texture(entry_file.path().string(), textureMap[filePath.filename().string()].width, 
                                                                    textureMap[filePath.filename().string()].height, textureMap[filePath.filename().string()].scale);
                            }
                            if(texture != nullptr){
                                TextureContainer[filePath.filename().string()] = std::move(texture);
                            } else if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "Texture_properties")) {
                                LOG("WARNING", "texture is not loaded " + entry_file.path().string());
                            }
                            break;
                        case AUDIO_DIR:
                            if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "properties")){
                                audio = Preloader::load_audio(entry_file.path().string());
                            }
                            if(audio != nullptr){
                                AudioContainer[filePath.filename().string()] = audio;
                            }
                            break;
                        case MAP_DIR:
                            if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "properties")){
                                map = Preloader::load_file(entry_file.path().string());
                            }
                            if(map != ""){
                                MapContainer[filePath.filename().string()] = map;
                            } else if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "properties")) {
                                LOG("WARNING", "map is not loaded " + entry_file.path().string());
                            }
                            break;
                        case FONT_DIR:
                            if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "Font_properties")){
                                font = Preloader::load_font(entry_file.path().string(), fontMap[filePath.filename().string()]);
                            }
                            if(font != nullptr){
                                FontsContainer[filePath.filename().string()] = font;
                            } else if(!(filePath.filename().string() == ".DS_Store") && !(filePath.filename().string() == "Font_properties")) {
                                LOG("WARNING", "font is not loaded " + entry_file.path().string());
                            }
                            break;
    
                        default:
                            break;
                    }
                }
                /*LOGGER*/
                switch (i){
                    case TEXTURES_DIR:
                        LOG("RESOURCE MANAGER", "texture is loaded!");
                        break;
                    case AUDIO_DIR:
                        LOG("RESOURCE MANAGER", "audio is loaded!");
                        break;
                    case MAP_DIR:
                        LOG("RESOURCE MANAGER", "maps is loaded!");
                        break;
                    case FONT_DIR:
                        LOG("RESOURCE MANAGER", "fonts is loaded!");
                        break;
                
                    default:
                        LOG("RESOURCE MANAGER", "error type");
                        break;
                }
            }
        } catch (const std::filesystem::filesystem_error& e){
            LOG("RESOURCE MANAGER ERROR", "filesystem error!", WHITE_RED_CODE);
            LOG("FATAL ERROR", e.what());
        }
        
        LOG("RESOURCE MANAGER", "all assets is preloaded!");
    }
    #endif
#endif

void ResourceManager::clear(){
    TextureContainer.clear();
    AudioContainer.clear();
    MapContainer.clear();
    for(auto& pair : FontsContainer){
        TTF_CloseFont(pair.second);
    }
     for(auto& pair : AudioContainer){
        Mix_FreeChunk(pair.second);
    }
    FontsContainer.clear();
}

Texture* ResourceManager::getTexture(std::string name){
    auto it = TextureContainer.find(name);
    if(it != TextureContainer.end()){
        return it->second.get();
    } else {
        LOG("RESOURCE MANAGER WARNING", "texture is not found " + name, YELLOW_CODE);
    }
    return nullptr;
}

std::string ResourceManager::getMap(std::string id){
    return MapContainer[id];
}

TTF_Font* ResourceManager::getFont(std::string name){
    return FontsContainer[name];
}

Mix_Chunk* ResourceManager::getAudio(std::string name){
    return AudioContainer[name];
}

void ResourceManager::saveFile(std::string text, std::string path){
    std::ofstream file(path);

    if(!file){
        LOG("WARNING", "file is not saved " + path);
        file.close();
        return;
    }

    file << text << std::endl;
    file.close();

    LOG("RESOURCE MANAGER", "file is saved to " + path);
}
