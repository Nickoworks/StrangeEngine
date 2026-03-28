#include "Texture.h"

#if RENDERER_OPENGL_MODE
Texture::Texture(int width, int height, std::string path, float scale) : scale(scale), alpha(1.0f){
    #ifdef __APPLE__
        #if TARGET_OS_IOS
            SDL_Surface* surface = IMG_Load(getIOSFilePath(path).c_str());  
        #else
            SDL_Surface* surface = IMG_Load(path.c_str());
        #endif
    #endif
    if(!surface){
        LOG("PRELOADER WARNING", "texture is not loaded from " + path, YELLOW_CODE);
        Texture::~Texture();
    } else {
        LOG("PRELOADER", "texture is loaded from " + path);
    }
    Texture::width = surface->w;
    Texture::height = surface->h;

    SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(surface);
    surface = formattedSurface;

    GLuint texture_;
    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

    // why mipmap makes segm fault

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // O-O

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(surface);
    Texture::texture = texture_;
}
#else
Texture::Texture(int width, int height, std::string path, float scale) : width(width), height(height), scale(scale){
    Texture::texture = IMG_LoadTexture(Renderer::getRenderer(), path.c_str());
    if(texture == NULL){
        LOG("PRELOADER WARNING", "texture is not loaded from " + path, YELLOW_CODE);
        Texture::~Texture();
    } else {
        LOG("PRELOADER", "texture is loaded from " + path);
    }
}
#endif

#if RENDERER_OPENGL_MODE
Texture::~Texture(){ 
    glDeleteTextures(1, &texture);
}
#else 
Texture::~Texture(){ 
    SDL_DestroyTexture(texture);
}
#endif

#if RENDERER_OPENGL_MODE
GLuint Texture::getTexture(){
    return texture; 
}
#else
SDL_Texture* Texture::getTexture(){
    return texture;
}
#endif

int Texture::getWidth(){
    return width;
}

int Texture::getHeight(){
    return height; 
}

float Texture::getScale(){
    return scale;
}


#if RENDERER_OPENGL_MODE
void Texture::setAlphaMode(float alpha){
    Texture::alpha = alpha;
    // glBindTexture(GL_TEXTURE_2D, texture);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glColor4f(r, g, b, alpha);
    // glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setColorMode(Uint8 r, Uint8 g, Uint8 b){
    Texture::r = r;
    Texture::g = g;
    Texture::b = b;
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor4f(r, g, b, alpha);
    glBindTexture(GL_TEXTURE_2D, 0);
}
#else 
void Texture::setAlphaMode(float alpha){
    Texture::alpha = alpha;
    // SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::setColorMode(Uint8 r, Uint8 g, Uint8 b){
    SDL_SetTextureColorMod(texture, r, g, b);
}
#endif
