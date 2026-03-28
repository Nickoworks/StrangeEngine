#pragma once
#include <iostream>
#include <vector>
#include "Renderer.h"
#include "Window.h"
#include "Events.h"
#include "AnimatedSprite.h"
#include "Entity.h"
#include "Physics.h"
#include "Texture.h"
#include "Tilemap.h"
#include "CollisionKit.h"
#include "ResourceManager.h"
#include "Audio.h"
#include "Vector2D.h"

enum Diractions{
    UP,
    DOWN, 
    LEFT,
    RIGHT
};

enum Static_frames{
    DOWN_FRAME=3,
    UP_FRAME=11,
    RIGHT_FRAME=17,
    LEFT_FRAME=25
};

class Player : public Entity{
    // int x;
    // int y;
    // int colliderDispX;
    // int colliderDispY;
    // int static_frame_ID;
    // int width;
    // int height;
    // bool isAnimation;
    // bool is_blocked;
    // SDL_Rect entity_rect;
    // SDL_Rect collision_rect;
    // SDL_Rect entity_tex_pos;
    // Texture* texture;
    // Animation animation;
    
public:
    static int xPrev;
    static int yPrev;
    static int direction;
    static int speed;
    static int level;
    static int  money;
    static int health;
    static int max_health;
    static int score;
    static int armorPow;
    static int attackPow;
    static bool player_move;
    static bool stopPlayer;
    static bool set_anim_once;
    static bool player_direction_up;
    static bool player_direction_down;
    static bool player_direction_right;
    static bool player_direction_left;
    static bool move_UP;
    static bool move_DOWN;
    static bool move_RIGHT;
    static bool move_LEFT;
    static bool sprint_;
    static std::string name;
    static std::string weapon;
    static std::string armor;

    Player(int x, int y, int width, int height, Texture* player_texture, SDL_Rect hit_box, bool is_blocked, std::string script, KinematicBody* physic_body, bool visible);
    ~Player();

    void sprint();
    void multiple_draw();
    void pollKeys();
    void move();
    // void change_player_rect(SDL_Rect rect);
};