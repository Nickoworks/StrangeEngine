#pragma once
#include "Renderer.h"
#include "Events.h"
#include "Texture.h"
#include "Window.h"
#include "AnimatedSprite.h"
#include "Tilemap.h"
#include "CollisionKit.h"
#include "ScriptRegistry.h"
#include "Physics.h"

#include <memory>
#include <vector>

class Entity{
protected:
    int colliderDispX;
    int colliderDispY;
    int static_frame_ID;
    int width;
    int height;
    bool is_blocked;
    bool visible;
    SDL_Rect entity_rect;
    SDL_Rect collision_rect;
    SDL_Rect entity_tex_pos;
    Texture* texture;
    AnimatedSprite animation;
    std::string script;
public:
    KinematicBody* physic_body;
    int x;
    int y;
    Entity(int width, int height, int x, int y, int static_frame_ID, bool is_blocked, Texture* texture, SDL_Rect hit_box, std::string script, KinematicBody* physic_body, bool visible);
    ~Entity();
    virtual void draw_hitbox(SDL_Color color);
    virtual void draw_static();
    virtual void draw_anim();
    virtual void draw_anim_once();
    virtual void change_y(int y_);
    virtual void change_x(int x_);
    virtual void change_rect(SDL_Rect rect);
    virtual void moveUP(int speed);
    virtual void moveDOWN(int speed);
    virtual void moveRIGHT(int speed);
    virtual void moveLEFT(int speed);
    virtual void changeAnim(std::vector<int> animComponent);
    virtual SDL_Rect getHitBox();
    virtual int getX();
    virtual int getY();
    virtual void _setCoordsWithIDframe();
    virtual void _updateRects();
    virtual SDL_Rect getRect();
    virtual int get_width();
    virtual int get_height();
    virtual void execScript();
};


