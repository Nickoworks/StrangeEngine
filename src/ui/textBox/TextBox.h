#pragma once
#include "UI.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "load_dialog.h"
#include "Text.h"
#include "Events.h"
#include "Timer.h"
#include "AnimatedSprite.h"
#include "Colors.h"
#include "Audio.h"
#include <sstream>
#include <stdio.h>
#include <vector>
#include "SDL_include.h"

class TextBox : public UI_Component{  
    int curr_str_char;
    int scale;
    bool is_played;
    int frame_x;
    int frame_y;
    int selectX;
    int selectY;
    int selected_option;
    bool up;
    Texture* frame_texture;
    TTF_Font* font;
    std::string text;
    Timer timer;
    std::vector<SDL_Rect> selection_rects;
    std::vector<std::string> selects;
public:
    std::string curr_text;
    TextBox(int x, int y, int scale, std::string text, TTF_Font* font, int char_delay, Texture* texture);
    TextBox(int x, int y, int frame_x, int frame_y, int scale, std::string text, TTF_Font* font, int char_delay, Texture* texture, Texture* frame_texture);
    TextBox(int x, int y, int scale, std::string text, TTF_Font* font, int char_delay, Texture* texture, std::vector<std::string> select, int selectX, int selectY);
    TextBox(int x, int y, int frame_x, int frame_y, int scale, std::string text, TTF_Font* font, int char_delay, Texture* texture, Texture* frame_texture, std::vector<std::string> select, int selectX, int selectY);
    void draw();
    void reset_text();
    bool isPlayed();
};
