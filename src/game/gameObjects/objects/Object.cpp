#include "Object.h"

Object::Object(int x, int y, int width, int height, int static_frame_ID, bool is_blocked, Texture* texture, SDL_Rect hit_box, std::string script, RigidBody* body, bool visible) : 
animation(animation.standart_anim_component, width, height, texture, visible), x(x), y(y), width(width), height(height), static_frame_ID(static_frame_ID),
is_blocked(is_blocked), texture(texture), collider_rect(hit_box), script(script), visible(visible), physic_rigid_body(body), physic_static_body(nullptr){
    colliderDispX = hit_box.x;
    colliderDispY = hit_box.y;
    physic_rigid_body->position.x = x;
    physic_rigid_body->position.y = y;
}

Object::Object(int x, int y, int width, int height, int static_frame_ID, bool is_blocked, Texture* texture, SDL_Rect hit_box, std::string script, StaticBody* body, bool visible) : 
animation(animation.standart_anim_component, width, height, texture, visible), x(x), y(y), width(width), height(height), static_frame_ID(static_frame_ID),
is_blocked(is_blocked), texture(texture), collider_rect(hit_box), script(script), visible(visible), physic_static_body(body), physic_rigid_body(nullptr){
    colliderDispX = hit_box.x;
    colliderDispY = hit_box.y;
    colliderPhysicDispX = physic_static_body->position.x;
    colliderPhysicDispY = physic_static_body->position.y;
    physic_static_body->position.x = x;
    physic_static_body->position.y = y;
}

Object::~Object(){
}

void Object::draw_hit_box(SDL_Color color){
    if(!visible){
        animation.visible = false;
    }
    if(visible){
        animation.visible = true;
    }
    _updateRects();
    Renderer::drawRect(collider_rect, color);
}

void Object::_updateRects(){
    if(physic_rigid_body == nullptr){
        rect.x = (physic_static_body->position.x - colliderPhysicDispX) - Camera::x;
        rect.y = (physic_static_body->position.y - colliderPhysicDispY) - Camera::y;
    } else if(physic_static_body == nullptr){
        rect.x = (physic_rigid_body->position.x - colliderDispX) - Camera::x;
        rect.y = (physic_rigid_body->position.y - colliderDispY) - Camera::y;
    }

    collider_rect.x = rect.x + colliderDispX;
    collider_rect.y = rect.y + colliderDispY;
    rect.w = width * texture->getScale();
    rect.h = height * texture->getScale();
}


void Object::_setCoordsWithIDframe(){
    int row = static_frame_ID / (texture->getWidth()/width);
    int col = static_frame_ID % (texture->getHeight()/height);

    rect_in_tex.x = col * width;
    rect_in_tex.y = row * height;
}

void Object::draw_static(){
    if(!visible){
        animation.visible = false;
    }
    if(visible){
        animation.visible = true;
    }
    _updateRects();

    _setCoordsWithIDframe();
    rect_in_tex.w = width;
    rect_in_tex.h = height;

    if(visible){
        Renderer::drawTexture(texture, rect_in_tex, rect);
    }
}

void Object::draw_anim(){
    if(!visible){
        animation.visible = false;
    }
    if(visible){
        animation.visible = true;
    }
    _updateRects();
    animation.draw_anim(rect);
}

void Object::changeAnim(std::vector<int> animComponent){
    animation.set_anim(animComponent);
}

SDL_Rect Object::getObjRect(){
    return Object::collider_rect;
}

void Object::execScript(){
    if(script == "NULL" || script == "null"){
        std::cout << "OBJECT: Script is not set!" << std::endl;
        return;   
    }
    ScriptRegistry::runScript(script);
}
