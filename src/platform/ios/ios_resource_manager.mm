#import <Foundation/Foundation.h>
#include "ios_resource_manager.h"
#include "ios_preloader.h"
#include "ios_file_system.h"

void ResourceManager::init(std::string paths[4]){
    std::string texture_prop_file = Preloader::load_file(paths[TEXTURES_DIR] + "/Texture_properties");
    std::string font_prop_file = Preloader::load_file(paths[FONT_DIR] + "/Font_properties");
    TextureMap textureMap = parseTextureProp(texture_prop_file);
    FontMap fontMap = parseFontProp(font_prop_file);

    @autoreleasepool {
        for(size_t i = 0; i < 4; i++) {
            NSString *resourcePath = [NSString stringWithUTF8String:paths[i].c_str()];
            NSFileManager *fileManager = [NSFileManager defaultManager];
            NSError *error = nil;
            NSArray *files = [fileManager contentsOfDirectoryAtPath:resourcePath error:&error];
            
            if (error) {
                LOG("RESOURCE MANAGER ERROR", "Failed to list directory contents for " + paths[i]);
                continue;
            }
            
            for (NSString *file in files) {
                std::string filePath = [file UTF8String];
                std::unique_ptr<Texture> texture = nullptr;
                Mix_Chunk* audio = nullptr;
                std::string map = "";
                TTF_Font* font = nullptr;

                if (![filePath isEqualToString:@".DS_Store"] && ![filePath isEqualToString:@"Texture_properties"] && ![filePath isEqualToString:@"Font_properties"]) {
                    switch (i) {
                        case TEXTURES_DIR: {
                            texture = Preloader::load_texture(filePath, textureMap[file].width, textureMap[file].height, textureMap[file].scale);
                            if (texture != nullptr) {
                                TextureContainer[filePath] = std::move(texture);
                            } else {
                                LOG("WARNING", "Texture is not loaded from " + filePath);
                            }
                            break;
                        }
                        case AUDIO_DIR: {
                            audio = Preloader::load_audio(filePath);
                            if (audio != nullptr) {
                                AudioContainer[filePath] = audio;
                            } else {
                                LOG("WARNING", "Audio is not loaded from " + filePath);
                            }
                            break;
                        }
                        case MAP_DIR: {
                            map = Preloader::load_file(filePath);
                            if (!map.empty()) {
                                MapContainer[filePath] = map;
                            } else {
                                LOG("WARNING", "Map is not loaded from " + filePath);
                            }
                            break;
                        }
                        case FONT_DIR: {
                            font = Preloader::load_font(filePath, fontMap[file]);
                            if (font != nullptr) {
                                FontsContainer[filePath] = font;
                            } else {
                                LOG("WARNING", "Font is not loaded from " + filePath);
                            }
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            
            switch (i) {
                case TEXTURES_DIR:
                    LOG("RESOURCE MANAGER", "Textures are loaded!");
                    break;
                case AUDIO_DIR:
                    LOG("RESOURCE MANAGER", "Audio is loaded!");
                    break;
                case MAP_DIR:
                    LOG("RESOURCE MANAGER", "Maps are loaded!");
                    break;
                case FONT_DIR:
                    LOG("RESOURCE MANAGER", "Fonts are loaded!");
                    break;
                default:
                    LOG("RESOURCE MANAGER", "Unknown resource type!");
                    break;
            }
        }
    }
    
    LOG("RESOURCE MANAGER", "All assets are preloaded!");
}
