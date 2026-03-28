#pragma once 
#include "SDL_include.h"
#include <iostream>
#include "AnimatedSprite.h"
#include "CollisionKit.h"
#include "Renderer.h"
#include "Events.h"
#include "Camera.h"
#include "Texture.h"
#include "Tilemap.h"
#include "ScriptRegistry.h"
#include "Physics.h"

class Object{
    int width;
    int height;
    int x;
    int y;
    int colliderDispX;
    int colliderDispY;
    int colliderPhysicDispX;
    int colliderPhysicDispY;
    int static_frame_ID;
    bool is_blocked;
    bool visible;
    SDL_Rect rect;
    SDL_Rect rect_in_tex;
    SDL_Rect collider_rect;
    AnimatedSprite animation;
    Texture* texture;
    std::string script;
public:
    RigidBody* physic_rigid_body;
    StaticBody* physic_static_body;
    Object(int x, int y, int width, int height, int static_frame_ID, bool is_blocked, Texture* texture, SDL_Rect hit_box, std::string script, RigidBody* body, bool visible);
    Object(int x, int y, int width, int height, int static_frame_ID, bool is_blocked, Texture* texture, SDL_Rect hit_box, std::string script, StaticBody* body, bool visible);
    ~Object();

    void draw_hit_box(SDL_Color color);
    void draw_anim();
    void draw_static(); // use static_frame_ID
    void _setCoordsWithIDframe();
    void _updateRects();
    void changeAnim(std::vector<int> animComponent);
    SDL_Rect getObjRect();
    void execScript();
};
