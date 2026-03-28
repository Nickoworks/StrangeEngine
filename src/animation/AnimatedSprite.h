#pragma once
#include "SDL_include.h"
#include <vector>
#include "Texture.h"
#include "Renderer.h"
#include "Window.h"
struct AnimatedSprite{
public:
    bool played_once;
    int xPos;
    int yPos;
    int frameWidth;
    int frameHeight;
    int animation_frames;
    int start_animation_frame;
    int animation_index;
    int frame_per_milsec;
    int current_frame;
    int frame_last_change;
    bool visible;
    SDL_Rect rect_tex;
    Texture* texture;
    static std::vector<int> standart_anim_component;

    AnimatedSprite(std::vector<int> anim_component, int frameWidth, int frameHeight, Texture* texture_, bool visible);
    void draw_anim(SDL_Rect rect_);
    void draw_anim_once_played(SDL_Rect rect_);
    void set_anim(std::vector<int> anim_component);
    void set_played_once(bool value);
    std::vector<int> get_anim_comp();
    void _set_frame();
};
