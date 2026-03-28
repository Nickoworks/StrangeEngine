#include "TextBox.h"
// TextBox::TextBox(int x, int y, Texture* texture_for_ui_comp) :
// UI_Component(x, y, texture_for_ui_comp), 
// animation(animation.standart_anim_component, 
// texture_for_ui_comp->getWidth(), 
// texture_for_ui_comp->getHeight(), 
// texture_for_ui_comp){
//     tranceparent_value = 255;
//     animation.played_once = false;
//     animation.frame_per_milsec = 5;
// }

TextBox::TextBox(int x, int y, int scale, std::string text, TTF_Font* font, int char_delay, Texture* texture) : 
UI_Component(x, y, texture), text(text), font(font), timer(char_delay), scale(scale){
    curr_str_char = 0;
    curr_text = "";
    is_played = false;
    frame_texture = nullptr;
    selects.clear();
    selected_option = 0;
}

TextBox::TextBox(int x, int y, int frame_x, int frame_y, int scale, std::string text, TTF_Font* font, int char_delay, Texture* texture, Texture* frame_texture) : 
UI_Component(x, y, texture), text(text), font(font), timer(char_delay), scale(scale), frame_texture(frame_texture), frame_x(frame_x), frame_y(frame_y){
    curr_str_char = 0;
    curr_text = "";
    is_played = false;
    selects.clear();
    selected_option = 0;
}

TextBox::TextBox(int x, int y, int scale, std::string text, TTF_Font* font, int char_delay, Texture* texture, std::vector<std::string> select, int selectX, int selectY) : 
UI_Component(x, y, texture), text(text), font(font), timer(char_delay), scale(scale), selects(select), selectX(selectX), selectY(selectY){
    curr_str_char = 0;
    curr_text = "";
    is_played = false;
    frame_texture = nullptr;

    int currCol = 0;
    int currX = 0;
    int textHeight;
    int textWidth;
    for(int i = 0; i < selects.size(); i++){
        TTF_SizeText(font, selects[i].c_str(), &textWidth, &textHeight);
        if(currX > 1){
            SDL_Rect rect = {(selectX + (currX * (textWidth+150))) - 30, (selectY + (((textHeight+30) * currCol))) - 30, textWidth + 30, textHeight + 30};

            selection_rects.push_back(rect);
            currX = 0;
            currCol++;
        } else {
            SDL_Rect rect = {(selectX + (currX * (textWidth+150))) - 30, (selectY + (((textHeight+30) * currCol))) - 30, textWidth + 30, textHeight + 30};

            selection_rects.push_back(rect);
            currX++;
        }
    }
    selected_option = 0;
}

TextBox::TextBox(int x, int y, int frame_x, int frame_y, int scale, std::string text, TTF_Font* font, int char_delay, Texture* texture, Texture* frame_texture, std::vector<std::string> select, int selectX, int selectY) : 
UI_Component(x, y, texture), text(text), font(font), timer(char_delay), scale(scale), frame_texture(frame_texture), frame_x(frame_x), frame_y(frame_y), selects(select), selectX(selectX), selectY(selectY){
    curr_str_char = 0;
    curr_text = "";
    is_played = false;
        int currCol = 0;
    int currX = 0;
    int textHeight;
    int textWidth;
    for(int i = 0; i < selects.size(); i++){
        TTF_SizeText(font, selects[i].c_str(), &textWidth, &textHeight);
        if(currX > 1){
            SDL_Rect rect = {(selectX + (currX * (textWidth+150))) - 5, (selectY + (((textHeight+30) * currCol))) - 5, (textWidth * scale) + 7, (textHeight * scale) + 7};

            selection_rects.push_back(rect);
            currX = 0;
            currCol++;
        } else {
            SDL_Rect rect = {(selectX + (currX * (textWidth+150))) - 5, (selectY + (((textHeight+30) * currCol))) - 5, (textWidth * scale) + 7, (textHeight * scale) + 7};

            selection_rects.push_back(rect);
            currX++;
        }
    }
    selected_option = 0;
}

void TextBox::draw(){
    int text_x, text_y;
    text_x = x + 30;
    text_y = y + 30;
    draw_template();

    Text text_(curr_text, text_x, text_y, scale, font, WHITE);
    if(timer.isFinished()){
        if(curr_text != text){
            curr_text = text.substr(0, curr_str_char);
            curr_str_char++;
            if(!Audio::is_playing_sound("text.wav")){
                Audio::play_sound("text.wav");
            }
        }
        timer.start();
    }
    text_.draw();

    if(frame_texture != nullptr){
        SDL_Rect rect = {frame_x, frame_y, 
        static_cast<int>(frame_texture->getWidth()*frame_texture->getScale()), 
        static_cast<int>(frame_texture->getHeight()*frame_texture->getScale())};
        Renderer::drawTexture(frame_texture, rect);
    }

    if(!selects.empty()){
        int currCol = 0;
        int currX = 0;
        int textHeight;
        int textWidth;
        for(int i = 0; i < selects.size(); i++){
            TTF_SizeText(font, selects[i].c_str(), &textWidth, &textHeight);
            if(currX > 1){
                Text text_(selects[i], selectX + (currX * (textWidth+150)), selectY + (((textHeight+30) * currCol)), scale, font, WHITE);
                text_.draw();
                currX = 0;
                currCol++;
            } else {
                Text text_(selects[i], selectX + (currX * (textWidth+150)), selectY + (((textHeight+30) * currCol)), scale, font, WHITE);
                text_.draw();
                currX++;
            }
        }
        if(Events::isKeyPressed(SDL_SCANCODE_X) && selects.size() > selected_option+1){
            selected_option++;
        }
        if(Events::isKeyPressed(SDL_SCANCODE_C) && 0 < selected_option){
            selected_option--;
        }
        // Renderer::drawRect(selection_rects[selected_option], WHITE);
        Text text_("> ", selection_rects[selected_option].x-20, selection_rects[selected_option].y+5, scale, font, WHITE);
        text_.draw();
    }

    if(curr_text != text){
        timer.update();
    } else if(curr_text == text){
        is_played = true;
    }
}

void TextBox::reset_text(){
    curr_str_char = 0;
    curr_text = "";
    is_played = false;
    selected_option = 0;
}

bool TextBox::isPlayed(){
    return is_played;
}

    //int time = Window::get_ticks();
    //if(animation.current_frame > animation.animation_frames+animation.start_animation_frame){
        //animation.current_frame = animation.start_animation_frame;
    //}
    //entity_rect.x = x + Tilemap::rect_tilemap.x;
    //entity_rect.y = y + Tilemap::rect_tilemap.y;
    //collision_rect.x = entity_rect.x + colliderDispX;
    //collision_rect.y = entity_rect.y + colliderDispY;
    //entity_rect.w = width * texture->getScale();
    //entity_rect.h = height * texture->getScale();
    //entity_tex_pos.w = width;
    //entity_tex_pos.h = height;
    //if(animation.frame_last_change+animation.frame_per_milsec < time){
       //Entity::_setFrame();
        //animation.frame_last_change = time;
        //animation.current_frame++;