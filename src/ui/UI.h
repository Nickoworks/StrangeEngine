#include "SDL_include.h"
#include "Renderer.h"
#include "Events.h"
#include "Window.h"
#include "Texture.h"

#pragma once

class UI_Component{ 
public:
    int x;
    int y;
    SDL_Rect rect;
    SDL_Rect rect_in_tex;
    Texture* texture;
    UI_Component(int x, int y, Texture* texture);
    ~UI_Component();  
    void draw_template();
};