#include "Entity.h"

Entity::Entity(int width, int height, int x, int y, int static_frame_ID, bool is_blocked, Texture* texture, SDL_Rect hit_box, std::string script, KinematicBody* physic_body, bool visible) : 
animation(animation.standart_anim_component, width, height, texture, visible), is_blocked(is_blocked), texture(texture), x(x), y (y), width(width),
height(height), static_frame_ID(static_frame_ID), collision_rect(hit_box), script(script), physic_body(physic_body), visible(visible){
    colliderDispX = hit_box.x;
    colliderDispY = hit_box.y;

    physic_body->position.x = x;
    physic_body->position.y = y;

    entity_rect.x = x;
    entity_rect.y = y;
    entity_rect.w = width;
    entity_rect.h = height;
}

Entity::~Entity(){
}

void Entity::draw_hitbox(SDL_Color color){
    _updateRects();
    Renderer::drawRect(Entity::collision_rect, color);
}

void Entity::_setCoordsWithIDframe(){
    int row = Entity::static_frame_ID / (texture->getWidth()/Entity::width);
    int col = Entity::static_frame_ID % (texture->getHeight()/Entity::height);

    entity_tex_pos.x = col * Entity::width;
    entity_tex_pos.y = row * Entity::height;
}

void Entity::draw_static(){
    if(!visible){
        animation.visible = false;
    }
    if(visible){
        animation.visible = true;
    }
    _updateRects();

    _setCoordsWithIDframe();
    entity_tex_pos.w = width;
    entity_tex_pos.h = height;

    if(visible){
        Renderer::drawTexture(texture, entity_tex_pos, entity_rect);
    }
}

void Entity::draw_anim(){
    if(!visible){
        animation.visible = false;
    }
    if(visible){
        animation.visible = true;
    }
    _updateRects();
    animation.draw_anim(entity_rect);
}

void Entity::draw_anim_once(){
    if(!visible){
        animation.visible = false;
    }
    if(visible){
        animation.visible = true;
    }
    _updateRects();
    animation.draw_anim_once_played(entity_rect);
}

void Entity::_updateRects(){
    entity_rect.x = physic_body->position.x - Camera::x - colliderDispX;
    entity_rect.y = physic_body->position.y - Camera::y - colliderDispY;
    collision_rect.x = entity_rect.x + colliderDispX;
    collision_rect.y = entity_rect.y + colliderDispY;
    entity_rect.w = width * texture->getScale();
    entity_rect.h = height * texture->getScale();
}

void Entity::change_x(int x_){
    Entity::x = x_;
}

void Entity::change_y(int y_){
    Entity::y = y_;
}

SDL_Rect Entity::getRect(){
    return Entity::entity_rect;
}

SDL_Rect Entity::getHitBox(){
    return Entity::collision_rect;
}

int Entity::get_width(){
    return Entity::width;
}

int Entity::get_height(){
    return Entity::height;
}

int Entity::getX(){
    return entity_rect.x + Camera::x;
}

int Entity::getY(){
    return entity_rect.y + Camera::y;
}

void Entity::changeAnim(std::vector<int> animComponent){
    animation.set_anim(animComponent);
}

void Entity::change_rect(SDL_Rect rect){
    collision_rect = rect;
}

void Entity::moveUP(int speed){
    entity_rect.y += speed;
}

void Entity::moveDOWN(int speed){
    entity_rect.y -= speed;
}

void Entity::moveRIGHT(int speed){
    entity_rect.x += speed;
}

void Entity::moveLEFT(int speed){
    entity_rect.h -= speed;
}

void Entity::execScript(){
    if(script == "NULL" || script == "null"){
        std::cout << "ENTITY: script is not set!" << std::endl;
        return;
    }
    ScriptRegistry::runScript(script);
}

