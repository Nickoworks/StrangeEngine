#include "Player.h"

// animation_frames = anim_component[0];
// start_animation_frame = anim_component[1];
// animation_index = anim_component[2];
// frame_per_milsec = anim_component[3];
// current_frame = anim_component[4];
// frame_last_change = anim_component[5];

// enum Static_frames{
//     DOWN_FRAME=3,
//     UP_FRAME=11,
//     RIGHT_FRAME=17,
//     LEFT_FRAME=25
// };

std::vector<int> Obj_Player_Anim_UP = {3, 8, 150, 8, 0};
std::vector<int> Obj_Player_Anim_DOWN = {3, 0, 150, 0, 0};
std::vector<int> Obj_Player_Anim_RIGHT = {1, 16, 200, 16, 0};
std::vector<int> Obj_Player_Anim_LEFT = {1, 24, 200, 24, 0};

int Player::direction = DOWN;
int Player::armorPow = 0;
int Player::attackPow = 0;
int Player::health = 100;
int Player::level = 0;
int Player::max_health = 100;
int Player::money = 0;
bool Player::player_move = false;
int Player::score = 0;
int Player::speed = 250;
bool Player::stopPlayer = false;
bool Player::sprint_ = false;
bool Player::set_anim_once = true;
bool Player::player_direction_up = false;
bool Player::player_direction_down = false;
bool Player::player_direction_right = false;
bool Player::player_direction_left = false;
bool Player::move_UP = true;
bool Player::move_DOWN = true;
bool Player::move_RIGHT = true;
bool Player::move_LEFT = true;
std::string Player::name = "Player";
std::string Player::weapon = "";
std::string Player::armor = "";

// Entity(int width, int height, int x, int y, int static_frame_ID, bool is_blocked, Texture* texture, SDL_Rect hit_box);

Player::Player(int x, int y, int width, int height, Texture* player_texture, SDL_Rect hit_box, bool is_blocked, std::string script, KinematicBody* physic_body, bool visible) : Entity(width, height, x, y, 
Player::direction, is_blocked, player_texture, hit_box, script, physic_body, visible){
    // player_rect.x = x;
    // player_rect.y = y;
    // colliderDispX = rect.x;
    // colliderDispY = rect.y;
    // player_rect.w = width * player_texture->getScale();
    // player_rect.h = height * player_texture->getScale();
}

Player::~Player(){
}

void Player::multiple_draw(){
    switch(direction){
        case UP:
            static_frame_ID = UP_FRAME;
            break;
        case DOWN:
            static_frame_ID = DOWN_FRAME;
            break;
        case LEFT:
            static_frame_ID = LEFT_FRAME;
            break;
        case RIGHT:
            static_frame_ID = RIGHT_FRAME;
            break;
        default:
            break;
    }
    if(player_move){ 
        if(set_anim_once){
            if(player_direction_up){
                animation.set_anim(Obj_Player_Anim_UP);
                set_anim_once = false;
            }
            if(player_direction_down){
                animation.set_anim(Obj_Player_Anim_DOWN);
                set_anim_once = false;
            }
            if(player_direction_left){
                animation.set_anim(Obj_Player_Anim_LEFT);
                set_anim_once = false;
            }
            if(player_direction_right){
                animation.set_anim(Obj_Player_Anim_RIGHT);
                set_anim_once = false;
            } 
        }  
        draw_anim();
    }
    else if(!player_move){
        draw_static();
    }
}

void Player::sprint(){
    if(sprint_){
        animation.frame_per_milsec = 100;
        speed = 400;
    } else {
        animation.frame_per_milsec = 150;
        speed = 250;
    }
}

void Player::pollKeys(){
    if(Events::events.type == SDL_KEYDOWN){
        if(Events::currentKeyState[SDL_SCANCODE_W] && move_UP){player_direction_up = true; player_move = true; direction = UP;}
        if(Events::currentKeyState[SDL_SCANCODE_S] && move_DOWN){player_direction_down = true; player_move = true; direction = DOWN;}
        if(Events::currentKeyState[SDL_SCANCODE_D] && move_RIGHT){player_direction_right = true; player_move = true; direction = RIGHT;}
        if(Events::currentKeyState[SDL_SCANCODE_A] && move_LEFT){ player_direction_left = true; player_move = true; direction = LEFT;}

        if(Events::currentKeyState[SDL_SCANCODE_LSHIFT]){
            sprint_ = true;
        }
    }
    if(Events::events.type == SDL_KEYUP){
        if(!Events::currentKeyState[SDL_SCANCODE_W] && move_UP){player_direction_up = false; set_anim_once = true;}
        if(!Events::currentKeyState[SDL_SCANCODE_S] && move_DOWN){player_direction_down = false; set_anim_once = true;}
        if(!Events::currentKeyState[SDL_SCANCODE_D] && move_RIGHT){player_direction_right = false; set_anim_once = true;}
        if(!Events::currentKeyState[SDL_SCANCODE_A] && move_LEFT){player_direction_left = false; set_anim_once = true;}

        if(!Events::currentKeyState[SDL_SCANCODE_LSHIFT]){
            sprint_ = false;
        }

        if(!Events::currentKeyState[SDL_SCANCODE_W] && !Events::currentKeyState[SDL_SCANCODE_A] &&
        !Events::currentKeyState[SDL_SCANCODE_S] && !Events::currentKeyState[SDL_SCANCODE_D]){
            player_move = false;
            set_anim_once = true;
        }
    }
    sprint();
}

void Player::move(){
    if(player_direction_up && !player_direction_down){
        physic_body->velocity.y = -130;
    }
    if(player_direction_down && !player_direction_up){
        physic_body->velocity.y = 130;
    }
    if(player_direction_right && !player_direction_left){
        physic_body->velocity.x = 130;
    }
    if(player_direction_left && !player_direction_right){
        physic_body->velocity.x = -130;
    }

    if(!player_direction_down && !player_direction_up){
        physic_body->velocity.y = 0;
    }
    if(!player_direction_left && !player_direction_right){
        physic_body->velocity.x = 0;
    }

    if((player_direction_right && player_direction_up) || 
            (player_direction_left && player_direction_up) || 
            (player_direction_right && player_direction_down) || 
            (player_direction_left && player_direction_down)){

        Vector2D velocity = physic_body->velocity;
        if(velocity.length() != 0){
            velocity = velocity.normalized();
        }
        physic_body->velocity = velocity * 130;
    }

    if(player_direction_up || player_direction_down || player_direction_right || player_direction_left){
        if(!Audio::is_playing_sound("step.wav")){
            Audio::play_sound("step.wav");
        }
    }
}
                                                