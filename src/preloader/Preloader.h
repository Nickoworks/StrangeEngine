#pragma once
#include "SDL_include.h"
#include "SDL_image_include.h"
#include "SDL_ttf_include.h"
#include "SDL_mixer_include.h"

#include <iostream>
#include "load_file.h"
#include "Logger.h"
#include <memory>
#include "Texture.h"

class Texture;
class Preloader{
public:
    static std::string load_file(std::string path);
    static std::unique_ptr<Texture> load_texture(std::string path, int width, int height, float scale);
    static TTF_Font* load_font(std::string path, int size);
    static Mix_Chunk* load_audio(std::string path);
};
