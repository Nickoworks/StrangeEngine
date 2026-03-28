#include <iostream>
#include <sstream>
#include "SDL_include.h"
#include "SDL_ttf_include.h"

#include "Renderer.h"

#pragma once

class Text{

public:
    Text(std::string text, int x, int y, int size, TTF_Font* font, SDL_Color color);
    ~Text();
    TTF_Font* font;
    std::string text;
    int x;
    int y;
    SDL_Color color;
    int size;
    SDL_Texture* rendered_text;
    void draw();
    void close_ttf();
    int get_size();
    void changeColor(SDL_Color color);
    void change_text(std::string text_);
};