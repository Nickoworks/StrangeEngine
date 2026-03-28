#pragma once
#include "SDL_include.h"
#include "Tilemap.h"
#include "Renderer.h"
#include "Window.h"
#include "Events.h"
#include "constants.h"

class Camera{
public:
    static bool freeCam;
    static int cameraScale;
    static int x, y;
    static int width, height;
    Camera(int startTargetX, int startTargetY);
    static void update(int targetX, int targetY, float smoth);
    static SDL_Rect getRect();
};
