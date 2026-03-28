#include <iostream>
#include "SDL_include.h"
#include "SDL_ttf_include.h"

#include "Window.h"
#include "constants.h"

SDL_Window* Window::window;
int Window::fps = FPS;
int Window::width = WINDOW_WIDTH;
int Window::height = WINDOW_HEIGHT;
int Window::positionX = SDL_WINDOWPOS_CENTERED;
int Window::positionY = SDL_WINDOWPOS_CENTERED;
const char* Window::title;
bool Window::fullscreen = false;

int Window::initialise(const char* title, int width, int height){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0 ){ 
        std::cout << "SDL_Init error :: " << SDL_GetError();
        return -1;
    }
    if(SDL_WINDOW_FULLSCREEN_DESKTOP > 0){
        fullscreen = true;
    } else {
        fullscreen = false;
    }

    if(!RENDERER_OPENGL_MODE){
        Window::window = SDL_CreateWindow(title, Window::positionX, Window::positionY, width, height, FULLSCREEN_DEFAULT);
    } else {
        Window::window = SDL_CreateWindow(title, Window::positionX, Window::positionY, width, height, FULLSCREEN_DEFAULT | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    }

    if(Window::window == NULL){
        std::cout << "SDL_CreateWindow error :: " << SDL_GetError();
        return -1;
    }
    if(TTF_Init() == -1){
        std::cout << "SDL_TTF error :: " << TTF_GetError();
        return -1;
    }

    return 0;
}

void Window::setFullScreen(bool fullscreen_){
    if(fullscreen_){
        fullscreen = true;
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        fullscreen = false;
        SDL_SetWindowFullscreen(window, 0);
    }
}

void Window::terminate(){
    SDL_Quit();
}

SDL_Window* Window::getWindow(){
    return Window::window;
}

void Window::destroy(){
    SDL_DestroyWindow(window);
}

int Window::get_ticks(){
    return SDL_GetTicks();
}

void Window::delay(int milsec){
    SDL_Delay(milsec);
}

void Window::setWindowSize(int w, int h){
    SDL_SetWindowSize(window, w, h);
    width = w;
    height = h;
}

void Window::setWindowTitle(const char* title_){
    SDL_SetWindowTitle(window, title_);
    title = title_;
}

void Window::setWindowPos(int posX, int posY){
    SDL_SetWindowPosition(window, posX, posY);
    positionX = posX;
    positionY = posY;
}
