#include "Camera.h"


bool Camera::freeCam = false;
int Camera::cameraScale = 1;
int Camera::x = 0;
int Camera::y = 0;
int Camera::width = WINDOW_WIDTH;
int Camera::height = WINDOW_HEIGHT;

bool UP;
bool DOWN;
bool RIGHT;
bool LEFT;

Camera::Camera(int startTargetX, int startTargetY){
    Camera::x = startTargetX - (width / 2);
    Camera::y = startTargetY - (height / 2); 
}

void Camera::update(int targetX, int targetY, float smoth){
    if(!freeCam){
        Camera::x = targetX - (width / 2);
        Camera::y = targetY - (height / 2); 
    } else if(freeCam){
        if(Events::currentKeyState[SDL_SCANCODE_I]){UP = true;}
        if(Events::currentKeyState[SDL_SCANCODE_K]){DOWN = true;}
        if(Events::currentKeyState[SDL_SCANCODE_L]){RIGHT = true;}
        if(Events::currentKeyState[SDL_SCANCODE_J]){LEFT = true;}

        if(!Events::currentKeyState[SDL_SCANCODE_I]){UP = false;}
        if(!Events::currentKeyState[SDL_SCANCODE_K]){DOWN = false;}
        if(!Events::currentKeyState[SDL_SCANCODE_L]){RIGHT = false;}
        if(!Events::currentKeyState[SDL_SCANCODE_J]){LEFT = false;}

        if(UP){y-=4;}
        if(DOWN){y+=4;}
        if(RIGHT){x+=4;}
        if(LEFT){x-=4;}
    }
}

SDL_Rect Camera::getRect(){
    return {x, y, width, height};
}
