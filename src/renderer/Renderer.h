#ifndef RENDERER
#define RENDERER
#include "SDL_include.h"
#include "SDL_image_include.h"
#include "SDL_ttf_include.h"

#include <vector>
#include "ConfiguredSprite.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "VBO.h"
#include "VAO.h"
#include "Logger.h"
#include "CollisionKit.h"
#include "ShaderManager.h"
#include <sstream>
#include <functional>

#include "OpenGL_include.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cassert>

class Renderer{
private:
    static SDL_Renderer* renderer;
    static SDL_GLContext glcontext;
public:
    static glm::mat4 projection;
    
    static VAO texture_vao;
    static VBO texture_vbo;
    static VAO surface_vao;
    static VBO surface_vbo;
    static VAO basic_vao;
    static VBO basic_vbo;

    static bool vsync;
    static int videoAdapterIndex;
    static int initialise(SDL_Window* window, int videoAdapterIndex, bool vsync_);
    static int initialise(SDL_Window* window, int videoAdapterIndex, bool vsync_, std::string mode);
    static void updateScreen(SDL_Window* window);
    static void clearRenderer();
    static SDL_Renderer* getRenderer();
    static SDL_GLContext getGLContext();
    static void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    static void drawTexture(Texture* texture, SDL_Rect rect_pos_tex, SDL_Rect rect_pos);
    static void drawTexture(Texture* texture, SDL_Rect rect_pos);
    static void drawTexture(Texture* texture);
    static void drawTextureEx(Texture* texture, SDL_Rect rect_pos, SDL_Rect rect_pos_tex, int angle, bool flipH, bool flipV);
    static void drawTextureEx(Texture* texture, SDL_Rect rect_pos, int angle, bool flipH, bool flipV);
    static void drawTextureEx(Texture* texture, int angle, bool flipH, bool flipV);

    static void drawSurface(SDL_Surface* surf, SDL_Rect rect, std::string shaderName);

    static void renderToTexture(SDL_Texture* texture, std::function<void()> renderContent, bool need_tex_clear);

    static void drawRect(SDL_Rect rect, SDL_Color color);
    static void drawFillRect(SDL_Rect rect, SDL_Color color);
    static void drawLine(int x1, int y1, int x2, int y2, SDL_Color color);
    static SDL_Texture* createTextureFromSurface(SDL_Surface* surface);
    static void destroy();
    static void clear_mem();
};
#endif