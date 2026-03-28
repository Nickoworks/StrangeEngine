#pragma once
#include "SDL_include.h"
#include "OpenGL_include.h"
#include <vector>
#include "Texture.h"
#include "Renderer.h"
#include "Window.h"
#include "constants.h"
#include "Vector2D.h"
#include "ShaderManager.h"
#include "ShaderProgram.h"
#include "Logger.h"
#include "VBO.h"
#include "VAO.h"
#include <cstdlib>
#include <ctime>

using Color = SDL_Color;

namespace VFX{
    extern VAO vfx_vao;
    extern VBO vfx_vbo;

    void init();
    void delete_buffers();

    class Vingette{
    public:
        Texture* texture;
        Vingette(Texture* texture);
        void draw();
    };


    struct Particle{
        Vector2D<int> position;
        Vector2D<float> velocity;
        float lifespan;
        float age;
        SDL_Color color;
        int w;
        int h;
    };
    class Particles{
        SDL_Rect emit_rect;
        SDL_Rect particle_rect;
        Texture* texture;
        Vector2D<float> velocity;
        int lifespan;
        int maxParticles;
        int emit_duration;
        int frame_last_change;
        SDL_Color color;
        int w;
        int h;
        bool visible;
        bool is_emited;
        std::vector<Particle> particles;
    public:
        Particles(Texture* texture, 
        Vector2D<float> velocity, 
        SDL_Rect emit_rect, 
        float lifespan, 
        int maxParticles,
        int emit_duration, bool visible, bool is_emited);

        Particles(SDL_Color color, 
        Vector2D<float> velocity, 
        SDL_Rect emit_rect,
        int w,
        int h, 
        float lifespan, 
        int maxParticles,
        int emit_duration, bool visible, bool is_emited);

        void emit();
        void update();
    };

    class Light{
    public:
        Vector2D<int> pos;
        float intencity;
        float size;
        float centralOpacity;
        float distance;
        int shapeType;
        Vector2D<float> shapeTransform;
        Color startColor;
        Color glowColor;

        Light(Vector2D<int> pos_, 
        float intencity_, 
        float size_, 
        float centralOpacity_,
        float distance_, 
        int shapeType_, 
        Vector2D<float> shapeTransform_,
        Color startColor_,
        Color glowColor_);

        void draw();
    };      
}
