#ifndef WINDOW
#define WINDOW
#include "SDL_include.h"

class Window{
public:
    static SDL_Window* window;
    static const char* title;
    static int fps;
    static int width;
    static int height;
    static int positionX;
    static int positionY;
    static bool fullscreen;

    static int initialise(const char* title, int width, int height);
    static void terminate();
    static SDL_Window* getWindow();
    static void setFullScreen(bool fullscreen_);
    static void destroy();
    static int get_ticks();
    static void delay(int milsec);
    static void setWindowSize(int w, int h);
    static void setWindowTitle(const char* title_);
    static void setWindowPos(int posX, int posY);
};
#endif 