#include "AnimatedSprite.h"

std::vector<int> AnimatedSprite::standart_anim_component = {0, 0, 0, 0, 0};

AnimatedSprite::AnimatedSprite(std::vector<int> animComponent, int frameWidth_, int frameHeight_, Texture* texture, bool visible) : animation_frames(animComponent[0]),
start_animation_frame(animComponent[1]), frame_per_milsec(animComponent[2]), current_frame(animComponent[3]),
frame_last_change(animComponent[4]), frameWidth(frameWidth_), frameHeight(frameHeight_), texture(texture), visible(visible){
    xPos = 0;
    yPos = 0;
    rect_tex = {0, 0, frameWidth, frameHeight};
    played_once = false;
}

void AnimatedSprite::draw_anim(SDL_Rect rect_){
    int time = Window::get_ticks();
    if(current_frame > animation_frames+start_animation_frame){
        current_frame = start_animation_frame;
    }

    if(frame_last_change+frame_per_milsec < time){
        _set_frame();
        frame_last_change = time;
        current_frame++;
    }
    if(visible){
        Renderer::drawTexture(texture, rect_tex, rect_);
    }
}

void AnimatedSprite::draw_anim_once_played(SDL_Rect rect_){
    int time = Window::get_ticks();
    if(current_frame > animation_frames+start_animation_frame){
        current_frame = start_animation_frame;
        played_once = true;
        _set_frame();
    }

    if(frame_last_change+frame_per_milsec < time && !played_once){
        _set_frame();
        frame_last_change = time;
        current_frame++;
    }
    if(visible){
        Renderer::drawTexture(texture, rect_tex, rect_);
    } 
}

void AnimatedSprite::set_anim(std::vector<int> anim_component){
    animation_frames = anim_component[0];
    start_animation_frame = anim_component[1];
    frame_per_milsec = anim_component[2];
    current_frame = anim_component[3];
    frame_last_change = anim_component[4];
}   

void AnimatedSprite::set_played_once(bool value){
    played_once = value;
}

std::vector<int> AnimatedSprite::get_anim_comp(){
    return {animation_frames, 
    start_animation_frame, 
    frame_per_milsec, 
    current_frame, 
    frame_last_change};
}

void AnimatedSprite::_set_frame(){
    int cols = texture->getWidth() / frameWidth;

    int row = current_frame / cols;
    int col = current_frame % cols;

    rect_tex.x = col * frameWidth;
    rect_tex.y = row * frameHeight;
}
