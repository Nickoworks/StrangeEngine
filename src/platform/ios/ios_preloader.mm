#import <Foundation/Foundation.h>
#include "ios_preloader.h"
#include "ios_file_system.h"
#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Texture.h"

std::string Preloader::load_file(std::string path){
    std::string data = ::load_file(getIOSFilePath(path));
    if(data == ""){
        LOG("WARNING", "file is empty or not loaded from " + path);
    } else {
        LOG("PRELOADER", "file is loaded from " + path);
    }
    return data;
}

std::unique_ptr<Texture> Preloader::load_texture(std::string path, int width, int height, float scale){
    std::unique_ptr<Texture> texture = std::make_unique<Texture>(width, height, path, scale);
    return texture;
}

TTF_Font* Preloader::load_font(std::string path, int size){
    TTF_Font* font = TTF_OpenFont(getIOSFilePath(path).c_str(), size);
    if(font == nullptr){
        LOG("WARNING", "font is not loaded from " + path);
        LOG("DISCLAIMER", "don't use this font but this font is nullptr", WHITE_RED_CODE);
        return nullptr;
    }
    LOG("PRELOADER", "font is loaded from " + path);
    return font;
}

Mix_Chunk* Preloader::load_audio(std::string path){
    SDL_RWops* rw = SDL_RWFromFile(getIOSFilePath(path).c_str(), "rb");
    if(rw == NULL){
        SDL_RWclose(rw);
        LOG("WARNING", "audio file is not opened!");
        return nullptr;
    }

    Mix_Chunk* audio = Mix_LoadWAV_RW(rw, 1);
    if(audio == NULL){
        LOG("WARNING", "audio is not loaded from " + path);
        LOG("DISCLAIMER", "don't use this audio but it nullptr");
        return nullptr;
    }
    LOG("PRELOADER", "audio is loaded from " + path);
    return audio;
}




