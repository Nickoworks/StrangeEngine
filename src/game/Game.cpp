#include "Game.h"

bool Game::running = true;
std::string Game::assets_path_sprites;
std::string Game::assets_path_tile_sets;
std::string Game::assets_path_mus;
std::string Game::assets_path_level_files;
int Game::startFrame;
float Game::deltaTime;
float Game::currentFPS;

//int animation_frames;
//int start_animation_frame;
//int animation_index;
//int frame_per_milsec;
//int current_frame;
//int frame_last_change;


void Game::game_loop(){
    // init rand int gen
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    //fps preference
    deltaTime = 1.f / Window::fps;
    startFrame = Window::get_ticks();
    int desiredDelta = 1000/Window::fps;
    int frameCount = 0;
    int currFrame;

    int lastTime = Window::get_ticks();
    regScripts();
    Scene::preload(Preloader::load_file("../res/scenes.dat/main.s"));

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    float x = 400.0f;
    float y = 300.0f;

    while(running){ 
        frameCount++;
        currFrame = Window::get_ticks();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Events::pollEvents(Game::running);
        Scene::execute();
        devscript_fps(currentFPS);  
        if(Events::events.type == SDL_KEYDOWN){
            if(Events::currentKeyState[SDL_SCANCODE_F8]){
                if(Window::fullscreen){
                    Window::setFullScreen(false);
                } else if(!Window::fullscreen){
                    Window::setFullScreen(true);
                }
            }
            if(Events::currentKeyState[SDL_SCANCODE_ESCAPE]){
                running = false;
            }
        }

        Renderer::updateScreen(Window::getWindow());
        if(!RENDERER_OPENGL_MODE){
            Renderer::clearRenderer();
        }

        if(currFrame - startFrame >= 1000){
            currentFPS = frameCount;
            frameCount = 0;
            startFrame = currFrame;
        }
        int delta = Window::get_ticks() - currFrame;

        if(delta < desiredDelta){
            Window::delay(desiredDelta - delta);
        }
    }
}           
