#pragma once
#include "SDL_include.h"
#include "SDL_image_include.h"

#include "OpenGL_include.h"

#include "Logger.h"
#include "VAO.h"
#include "VBO.h"
#include "constants.h"
#include <iostream>

#ifdef __APPLE__
    #include <TargetConditionals.h>

    #if TARGET_OS_IOS
        #include "ios_file_system.h"
    #endif
#endif

class Texture{
#if RENDERER_OPENGL_MODE
    GLuint texture;
#else
    SDL_Texture* texture;
#endif
public:
    int width;
    int height;
    float scale;
    float alpha;
    float r;
    float g;
    float b;
    std::string path;
    
    Texture(int width, int height, std::string path, float scale);
    ~Texture();

#if RENDERER_OPENGL_MODE
    GLuint getTexture();
#else 
    SDL_Texture* getTexture();
#endif
    int getWidth();
    int getHeight();
    float getScale();
    void setAlphaMode(float alpha);
    void setColorMode(Uint8 r, Uint8 g, Uint8 b);
};
