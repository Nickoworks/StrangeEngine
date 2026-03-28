#include"Renderer.h"
#include "constants.h"
#include<iostream>
#include "SDL_include.h"
#include "OpenGL_include.h"
#include "SDL_image_include.h"
#include "Window.h"

SDL_Renderer* Renderer::renderer;
SDL_GLContext Renderer::glcontext;
int Renderer::videoAdapterIndex;
VAO Renderer::texture_vao(1);
VBO Renderer::texture_vbo;
VAO Renderer::surface_vao(1);
VBO Renderer::surface_vbo;
VAO Renderer::basic_vao(1);
VBO Renderer::basic_vbo;

glm::mat4 Renderer::projection = glm::ortho(0.0f, float(Window::width), float(Window::height), 0.0f, -1.0f, 1.0f);
static glm::mat4 standart_model = glm::mat4(1.0f);

int Renderer::initialise(SDL_Window* window, int videoAdapterIndex, bool vsync_){
    if(!RENDERER_OPENGL_MODE){
        if(vsync_){
            Renderer::renderer = SDL_CreateRenderer(window, videoAdapterIndex, SDL_RENDERER_ACCELERATED);
            SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
        } else {
            Renderer::renderer = SDL_CreateRenderer(window, videoAdapterIndex, 0);
        }
        if(Renderer::renderer == NULL) {
            std::ostringstream rendererError;
            rendererError << "SDL_CreateRenderer error " << SDL_GetError();
            LOG("RENDERER FATAL ERROR", rendererError.str(), RED_CODE);
            
            return -1;
        }
    } else {
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        if(vsync_){
            SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
            SDL_GL_SetSwapInterval(1);
        }
        glcontext = SDL_GL_CreateContext(window);

        if(Renderer::glcontext == NULL){
            std::ostringstream rendererError;
            rendererError << "SDL_GL_Create_Context error " << SDL_GetError();
            LOG("RENDERER FATAL ERROR", rendererError.str(), RED_CODE);
            return -1;
        }
    }

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        LOG("RENDERER FATAL ERROR", "Failed to initialize GLEW", RED_CODE);
    }

    const char* videoDriver = SDL_GetCurrentVideoDriver();
    std::ostringstream videoDriverLog;
    videoDriverLog << "current video driver " << videoDriver;
    LOG("RENDERER INFO", videoDriverLog.str(), GREEN_CODE);
    
    if(Renderer::renderer != NULL){
        SDL_RendererInfo info;
        SDL_GetRendererInfo(renderer, &info);
        std::ostringstream rendererLog;
        rendererLog << "current video renderer " << info.name;
        LOG("RENDERER INFO", rendererLog.str(), WHITE_CODE);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer_ = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);

    std::string renderer_str(reinterpret_cast<const char*>(renderer_));
    std::string vendor_str(reinterpret_cast<const char*>(vendor));
    std::string version_str(reinterpret_cast<const char*>(version));

    LOG("HARDWARE INFO", "Graphics card vendor: " + vendor_str, GREEN_CODE);
    LOG("HARDWARE INFO", "Graphics card model: " + renderer_str, GREEN_CODE);
    LOG("RENDERER INFO", "OpenGL Version: " + version_str, GREEN_CODE);

    // shader = ShaderProgram("../res/shaders.dat/texture.frag", "../res/shaders.dat/texture.vert");
    // basic_shader = ShaderProgram("../res/shaders.dat/basic.frag", "../res/shaders.dat/basic.vert");

    texture_vao = VAO();
    basic_vao = VAO();
    surface_vao = VAO();

    // SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    return 0;
}

int Renderer::initialise(SDL_Window* window, int videoAdapterIndex, bool vsync_, std::string mode){
    if(!RENDERER_OPENGL_MODE){
        if(vsync_){
            Renderer::renderer = SDL_CreateRenderer(window, videoAdapterIndex, SDL_RENDERER_ACCELERATED);
            SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
        } else {
            Renderer::renderer = SDL_CreateRenderer(window, videoAdapterIndex, 0);
        }
        if(Renderer::renderer == NULL) {
            std::ostringstream rendererError;
            rendererError << "SDL_CreateRenderer error " << SDL_GetError();
            LOG("RENDERER FATAL ERROR", rendererError.str(), RED_CODE);
            
            return -1;
        }
    } else {
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        if(vsync_){
            SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
            SDL_GL_SetSwapInterval(1);
        }
        glcontext = SDL_GL_CreateContext(window);

        if(Renderer::glcontext == NULL){
            std::ostringstream rendererError;
            rendererError << "SDL_GL_Create_Context error " << SDL_GetError();
            LOG("RENDERER FATAL ERROR", rendererError.str(), RED_CODE);
            return -1;
        }
    }

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        LOG("RENDERER FATAL ERROR", "Failed to initialize GLEW", RED_CODE);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const char* videoDriver = SDL_GetCurrentVideoDriver();
    std::ostringstream videoDriverLog;
    videoDriverLog << "current video driver " << videoDriver;
    LOG("RENDERER INFO", videoDriverLog.str(), GREEN_CODE);
    
    if(Renderer::renderer != NULL){
        SDL_RendererInfo info;
        SDL_GetRendererInfo(renderer, &info);
        std::ostringstream rendererLog;
        rendererLog << "current video renderer " << info.name;
        LOG("RENDERER INFO", rendererLog.str(), WHITE_CODE);
    }

    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer_ = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);

    std::string renderer_str(reinterpret_cast<const char*>(renderer_));
    std::string vendor_str(reinterpret_cast<const char*>(vendor));
    std::string version_str(reinterpret_cast<const char*>(version));

    LOG("HARDWARE INFO", "Graphics card vendor: " + vendor_str, GREEN_CODE);
    LOG("HARDWARE INFO", "Graphics card model: " + renderer_str, GREEN_CODE);
    LOG("RENDERER INFO", "OpenGL Version: " + version_str, GREEN_CODE);

    // shader = ShaderProgram("../res/shaders.dat/texture.frag", "../res/shaders.dat/texture.vert");
    // basic_shader = ShaderProgram("../res/shaders.dat/basic.frag", "../res/shaders.dat/basic.vert");

    texture_vao = VAO();
    basic_vao = VAO();
    surface_vao = VAO();

    // SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    return 0;
}

void Renderer::updateScreen(SDL_Window* window){
    projection = glm::ortho(0.0f, float(Window::width), float(Window::height), 0.0f, -1.0f, 1.0f);
    SDL_GL_SwapWindow(window);
}

void Renderer::clearRenderer(){
    SDL_RenderClear(Renderer::renderer);
}

SDL_Renderer* Renderer::getRenderer(){
    return Renderer::renderer;
}

#if RENDERER_OPENGL_MODE
void Renderer::destroy(){
    texture_vao.Unbind();

    texture_vao.Delete();
    texture_vbo.Delete();
    basic_vao.Delete();
    basic_vbo.Delete();
    surface_vao.Delete();
    surface_vbo.Delete();

    SDL_GL_DeleteContext(glcontext);
}

#else
void Renderer::destroy(){
    SDL_DestroyRenderer(Renderer::renderer);
}
#endif

void Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    SDL_SetRenderDrawColor(Renderer::renderer, r, g, b, a);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, SDL_Color color){
    if((x1 >= 0 && x1 <= Window::width && y1 >= 0 && y1 <= Window::height) &&
        (x2 >= 0 && x2 <= Window::width && y2 >= 0 && y2 <= Window::height)){
        ShaderProgram* shader = ShaderManager::getShader("basic");

        float vertices[] = {
            float(x1), float(y1), 0.0f,
            float(x2), float(y2), 0.0f,
        };

        glm::mat4 model = glm::mat4(1.0f);
        GLuint colorLoc = glGetUniformLocation(shader->shaderProgram, "Color");
        GLuint projectionLoc = glGetUniformLocation(shader->shaderProgram, "projection");
        GLuint modelLoc = glGetUniformLocation(shader->shaderProgram, "model");

        if(basic_vbo.buffer == 0){
            basic_vbo = VBO(vertices, sizeof(vertices));
        }
        basic_vbo.Update(vertices, sizeof(vertices));
        shader->use();

        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform4f(colorLoc, (GLfloat)color.r/255, (GLfloat)color.g/255, (GLfloat)color.b/255, (GLfloat)color.a/255);

        basic_vao.Bind();
        basic_vao.LinkAttrib(basic_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
        glDrawArrays(GL_LINE_LOOP, 0, 2);
    }    
}

#if RENDERER_OPENGL_MODE
void Renderer::drawTexture(Texture* texture, SDL_Rect rect_pos_tex, SDL_Rect rect_pos){
    if(CollisionKit::checkCollision(rect_pos, {0, 0, Window::width, Window::height})){
        ShaderProgram* shader = ShaderManager::getShader("texture");
        float u1 = (float)rect_pos_tex.x / (float)texture->width;
        float v1 = (float)(rect_pos_tex.y + rect_pos_tex.h) / (float)texture->height;
        float u2 = (float)(rect_pos_tex.x + rect_pos_tex.w) / (float)texture->width;
        float v2 = (float)rect_pos_tex.y / (float)texture->height;

        float vertices[] = {
            float(rect_pos.x), float(rect_pos.y), 0.0f, u1, v2,
            float(rect_pos.x + rect_pos.w), float(rect_pos.y), 0.0f, u2, v2,
            float(rect_pos.x + rect_pos.w), float(rect_pos.y + rect_pos.h), 0.0f, u2, v1,
            float(rect_pos.x), float(rect_pos.y + rect_pos.h), 0.0f, u1, v1
        };

        if(texture_vbo.buffer == 0){
            texture_vbo = VBO(vertices, sizeof(vertices));
            texture_vao.Bind();
            texture_vao.LinkAttrib(texture_vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
            texture_vao.LinkAttrib(texture_vbo, 1, 3, GL_FLOAT, 5 * sizeof(float), (void*)(3*sizeof(float)));
        }
        texture_vbo.Update(vertices, sizeof(vertices));

        glm::mat4 model = glm::mat4(1.0f);

        GLuint projectionLoc = glGetUniformLocation(shader->shaderProgram, "projection");
        GLuint modelLoc = glGetUniformLocation(shader->shaderProgram, "model");
        GLuint alphaLoc = glGetUniformLocation(shader->shaderProgram, "texture_alpha");

        shader->use();
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1f(alphaLoc, texture->alpha);

        glUniform2f(glGetUniformLocation(shader->shaderProgram, "resolution"), Window::width, Window::height);  
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getTexture());

        texture_vao.Bind();

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);  
    }
}

void Renderer::drawTexture(Texture* texture, SDL_Rect rect_pos){
    if(CollisionKit::checkCollision(rect_pos, {0, 0, Window::width, Window::height})){
        ShaderProgram* shader = ShaderManager::getShader("texture");

        float vertices[] = {
            float(rect_pos.x), float(rect_pos.y), 0.0f, -1.0f, 0.0f,
            float(rect_pos.x + rect_pos.w), float(rect_pos.y), 0.0f, 0.0f, 0.0f,
            float(rect_pos.x + rect_pos.w), float(rect_pos.y + rect_pos.h), 0.0f, 0.0f, 1.0f,
            float(rect_pos.x), float(rect_pos.y + rect_pos.h), 0.0f, -1.0f, 1.0f
        };

        if(texture_vbo.buffer == 0){
            texture_vbo = VBO(vertices, sizeof(vertices));
            texture_vao.Bind();
            texture_vao.LinkAttrib(texture_vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
            texture_vao.LinkAttrib(texture_vbo, 1, 3, GL_FLOAT, 5 * sizeof(float), (void*)(3*sizeof(float)));
        }
        texture_vbo.Update(vertices, sizeof(vertices));

        glm::mat4 model = glm::mat4(1.0f);

        GLuint projectionLoc = glGetUniformLocation(shader->shaderProgram, "projection");
        GLuint modelLoc = glGetUniformLocation(shader->shaderProgram, "model");
        GLuint alphaLoc = glGetUniformLocation(shader->shaderProgram, "texture_alpha");

        shader->use();
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1f(alphaLoc, texture->alpha);

        glUniform2f(glGetUniformLocation(shader->shaderProgram, "resolution"), Window::width, Window::height);  
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getTexture());

        texture_vao.Bind();

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);  
    }
}

void Renderer::drawTexture(Texture* texture){
    ShaderProgram* shader = ShaderManager::getShader("texture");
    float vertices[] = {
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        (float)Window::width, 0.0f, 0.0f, 0.0f, 0.0f,
        (float)Window::width, (float)Window::height, 0.0f, 0.0f, 1.0f,
        0.0f, (float)Window::height, 0.0f, -1.0f, 1.0f
    };

    if(texture_vbo.buffer == 0){
        texture_vbo = VBO(vertices, sizeof(vertices));
        texture_vao.LinkAttrib(texture_vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
        texture_vao.LinkAttrib(texture_vbo, 1, 3, GL_FLOAT, 5 * sizeof(float), (void*)(3*sizeof(float)));
    }
    texture_vbo.Update(vertices, sizeof(vertices));

    glm::mat4 projection = glm::ortho(0.0f, float(Window::width), float(Window::height), 0.0f, -1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    GLuint projectionLoc = glGetUniformLocation(shader->shaderProgram, "projection");
    GLuint modelLoc = glGetUniformLocation(shader->shaderProgram, "model");
    GLuint alphaLoc = glGetUniformLocation(shader->shaderProgram, "texture_alpha");

    shader->use();
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniform1f(alphaLoc, texture->alpha);

    glUniform2f(glGetUniformLocation(shader->shaderProgram, "resolution"), Window::width, Window::height);  

    texture_vao.Bind();

    glBindTexture(GL_TEXTURE_2D, texture->getTexture());

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Renderer::drawTextureEx(Texture* texture, SDL_Rect rect_pos, SDL_Rect rect_pos_tex, int angle, bool flipH, bool flipV){
    if(CollisionKit::checkCollision(rect_pos, {0, 0, Window::width, Window::height})){
        ShaderProgram* shader = ShaderManager::getShader("texture");
        float u1 = (float)rect_pos_tex.x / (float)texture->width;
        float v1 = (float)(rect_pos_tex.y + rect_pos_tex.h) / (float)texture->height;
        float u2 = (float)(rect_pos_tex.x + rect_pos_tex.w) / (float)texture->width;
        float v2 = (float)rect_pos_tex.y / (float)texture->height;

        if(flipH) std::swap(u1, u2);
        if(flipV) std::swap(v1, v2);

        float vertices[] = {
            float(rect_pos.x), float(rect_pos.y), 0.0f, u1, v2,
            float(rect_pos.x + rect_pos.w), float(rect_pos.y), 0.0f, u2, v2,
            float(rect_pos.x + rect_pos.w), float(rect_pos.y + rect_pos.h), 0.0f, u2, v1,
            float(rect_pos.x), float(rect_pos.y + rect_pos.h), 0.0f, u1, v1
        };

        if(texture_vbo.buffer == 0){
            texture_vbo = VBO(vertices, sizeof(vertices));
            texture_vao.Bind();
            texture_vao.LinkAttrib(texture_vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
            texture_vao.LinkAttrib(texture_vbo, 1, 3, GL_FLOAT, 5 * sizeof(float), (void*)(3*sizeof(float)));
        }
        texture_vbo.Update(vertices, sizeof(vertices));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)angle, glm::vec3(0.0f, 0.0f, 1.0f));

        GLuint projectionLoc = glGetUniformLocation(shader->shaderProgram, "projection");
        GLuint modelLoc = glGetUniformLocation(shader->shaderProgram, "model");
        GLuint alphaLoc = glGetUniformLocation(shader->shaderProgram, "texture_alpha");
        // GLuint timeLoc = glGetUniformLocation(shader->shaderProgram, "time");

        shader->use();
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1f(alphaLoc, texture->alpha);

        glUniform2f(glGetUniformLocation(shader->shaderProgram, "resolution"), Window::width, Window::height);  
        // glUniform1f(timeLoc, SDL_GetTicks() / 1000.0f);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getTexture());

        texture_vao.Bind();

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);  
    }
}

void Renderer::drawTextureEx(Texture* texture, SDL_Rect rect_pos, int angle, bool flipH, bool flipV){
    if(CollisionKit::checkCollision(rect_pos, {0, 0, Window::width, Window::height})){
        ShaderProgram* shader = ShaderManager::getShader("texture");
        float u1 = -1.0f;
        float v1 = 1.0f;
        float u2 = 0.0f;
        float v2 = 0.0f;

        float vertices[] = {
            float(rect_pos.x), float(rect_pos.y), 0.0f, u1, v2,
            float(rect_pos.x + rect_pos.w), float(rect_pos.y), 0.0f, u2, v2,
            float(rect_pos.x + rect_pos.w), float(rect_pos.y + rect_pos.h), 0.0f, u2, v1,
            float(rect_pos.x), float(rect_pos.y + rect_pos.h), 0.0f, u1, v1
        };

        if(flipH) std::swap(u1, u2);
        if(flipV) std::swap(v1, v2);

        if(texture_vbo.buffer == 0){
            texture_vbo = VBO(vertices, sizeof(vertices));
            texture_vao.LinkAttrib(texture_vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
            texture_vao.LinkAttrib(texture_vbo, 1, 3, GL_FLOAT, 5 * sizeof(float), (void*)(3*sizeof(float)));
        }
        texture_vbo.Update(vertices, sizeof(vertices));

        glm::mat4 projection = glm::ortho(0.0f, float(Window::width), float(Window::height), 0.0f, -1.0f, 1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)angle, glm::vec3(0.0f, 0.0f, 1.0f));

        GLuint projectionLoc = glGetUniformLocation(shader->shaderProgram, "projection");
        GLuint modelLoc = glGetUniformLocation(shader->shaderProgram, "model");
        GLuint alphaLoc = glGetUniformLocation(shader->shaderProgram, "texture_alpha");

        shader->use();
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1f(alphaLoc, texture->alpha);

        glUniform2f(glGetUniformLocation(shader->shaderProgram, "resolution"), Window::width, Window::height);  

        texture_vao.Bind();
        glBindTexture(GL_TEXTURE_2D, texture->getTexture());

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
}

void Renderer::drawTextureEx(Texture* texture, int angle, bool flipH, bool flipV){
    ShaderProgram* shader = ShaderManager::getShader("texture");
    float u1 = -1.0f;
    float v1 = 1.0f;
    float u2 = 0.0f;
    float v2 = 0.0f;

    float vertices[] = {
        0.0f, 0.0f, 0.0f, u1, v2,
        (float)Window::width, 0.0f, 0.0f, u2, v2,
        (float)Window::width, (float)Window::height, 0.0f, u2, v1,
        0.0f, (float)Window::height, 0.0f, u1, v1
    };
    
    if(flipH) std::swap(u1, u2);
    if(flipV) std::swap(v1, v2);

    if(texture_vbo.buffer == 0){
        texture_vbo = VBO(vertices, sizeof(vertices));
        texture_vao.LinkAttrib(texture_vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
        texture_vao.LinkAttrib(texture_vbo, 1, 3, GL_FLOAT, 5 * sizeof(float), (void*)(3*sizeof(float)));
    }
    texture_vbo.Update(vertices, sizeof(vertices));

    glm::mat4 projection = glm::ortho(0.0f, float(Window::width), float(Window::height), 0.0f, -1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)angle, glm::vec3(0.0f, 0.0f, 1.0f));

    GLuint projectionLoc = glGetUniformLocation(shader->shaderProgram, "projection");
    GLuint modelLoc = glGetUniformLocation(shader->shaderProgram, "model");
    GLuint alphaLoc = glGetUniformLocation(shader->shaderProgram, "texture_alpha");

    shader->use();
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniform1f(alphaLoc, texture->alpha);

    glUniform2f(glGetUniformLocation(shader->shaderProgram, "resolution"), Window::width, Window::height);  

    texture_vao.Bind();

    glBindTexture(GL_TEXTURE_2D, texture->getTexture());

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

#else
void Renderer::drawTexture(SDL_Texture* texture, SDL_Rect rect_pos_tex, SDL_Rect rect_pos){
    SDL_RenderCopy(Renderer::renderer, texture, &rect_pos_tex, &rect_pos);
}

void Renderer::drawTexture(SDL_Texture* texture, SDL_Rect rect_pos){
    SDL_RenderCopy(Renderer::renderer, texture, NULL, &rect_pos);s
}

void Renderer::drawTexture(SDL_Texture* texture){
    SDL_RenderCopy(Renderer::renderer, texture, NULL, NULL);
}

void Renderer::drawTextureEx(SDL_Texture* texture, SDL_Rect rect_pos, SDL_Rect rect_pos_tex, int angle, bool flipH, bool flipV){
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if(flipH){
        flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
    }
    
    if(flipV){
        flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
    }

    SDL_RenderCopyEx(renderer, texture, &rect_pos_tex, &rect_pos, angle, NULL, flip);
}

void Renderer::drawTextureEx(SDL_Texture* texture, SDL_Rect rect_pos, int angle, bool flipH, bool flipV){
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if(flipH){
        flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
    }
    
    if(flipV){
        flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
    }

    SDL_RenderCopyEx(renderer, texture, NULL, &rect_pos, angle, NULL, flip);
}

void Renderer::drawTextureEx(SDL_Texture* texture, int angle, bool flipH, bool flipV){
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if(flipH){
        flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
    }
    
    if(flipV){
        flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
    }

    SDL_RenderCopyEx(renderer, texture, NULL, NULL, angle, NULL, flip);
}
#endif

void Renderer::drawSurface(SDL_Surface* surf, SDL_Rect rect, std::string shaderName){
    ShaderProgram* shader = ShaderManager::getShader(shaderName);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLenum format;
    if (surf->format->BytesPerPixel == 4) {
        format = (surf->format->Rmask == 0x000000ff) ? GL_RGBA : GL_BGRA;
    } else if (surf->format->BytesPerPixel == 3) {
        format = (surf->format->Rmask == 0x000000ff) ? GL_RGB : GL_BGR;
    } else {
        std::cerr << "Unsupported pixel format" << std::endl;
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, surf->w, surf->h, 0, format, GL_UNSIGNED_BYTE, surf->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    float vertices[] = {
        float(rect.x), float(rect.y), 0.0f, -1.0f, 0.0f,
        float(rect.x + rect.w), float(rect.y), 0.0f, 0.0f, 0.0f,
        float(rect.x + rect.w), float(rect.y + rect.h), 0.0f, 0.0f, 1.0f,
        float(rect.x), float(rect.y + rect.h), 0.0f, -1.0f, 1.0f
    };

    if(surface_vbo.buffer == 0){
        surface_vbo = VBO(vertices, sizeof(vertices));
    }
    surface_vbo.Update(vertices, sizeof(vertices));

    surface_vao.Bind();
    surface_vao.LinkAttrib(surface_vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    surface_vao.LinkAttrib(surface_vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    GLuint projectionLoc = glGetUniformLocation(shader->shaderProgram, "projection");
    GLuint modelLoc = glGetUniformLocation(shader->shaderProgram, "model");

    glm::mat4 model = glm::mat4(1.0f);

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    shader->use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDeleteTextures(1, &texture);
    texture = 0;
}

void Renderer::renderToTexture(SDL_Texture* texture, std::function<void()> renderContent, bool need_tex_clear){
    SDL_SetRenderTarget(renderer, texture); 
    if(need_tex_clear){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }   
    renderContent();
    SDL_SetRenderTarget(renderer, NULL);
}

void Renderer::drawRect(SDL_Rect rect, SDL_Color color){
    if(CollisionKit::checkCollision(rect, {0, 0, Window::width, Window::height})){
        ShaderProgram* shader = ShaderManager::getShader("basic");

        float vertices[] = {
            float(rect.x), float(rect.y), 0.0f,
            float(rect.x + rect.w), float(rect.y), 0.0f,
            float(rect.x + rect.w), float(rect.y + rect.h), 0.0f,
            float(rect.x), float(rect.y + rect.h), 0.0f
        };

        glm::mat4 model = glm::mat4(1.0f);
        GLuint colorLoc = glGetUniformLocation(shader->shaderProgram, "Color");
        GLuint projectionLoc = glGetUniformLocation(shader->shaderProgram, "projection");
        GLuint modelLoc = glGetUniformLocation(shader->shaderProgram, "model");

        if(basic_vbo.buffer == 0){
            basic_vbo = VBO(vertices, sizeof(vertices));
        }
        basic_vbo.Update(vertices, sizeof(vertices));
        shader->use();

        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform4f(colorLoc, (GLfloat)color.r/255, (GLfloat)color.g/255, (GLfloat)color.b/255, (GLfloat)color.a/255);

        basic_vao.Bind();
        basic_vao.LinkAttrib(basic_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
}

void Renderer::drawFillRect(SDL_Rect rect, SDL_Color color){
    if(CollisionKit::checkCollision(rect, {0, 0, Window::width, Window::height})){
        ShaderProgram* shader = ShaderManager::getShader("basic");

        float vertices[] = {
            float(rect.x), float(rect.y), 0.0f,
            float(rect.x + rect.w), float(rect.y), 0.0f,
            float(rect.x + rect.w), float(rect.y + rect.h), 0.0f,
            float(rect.x), float(rect.y + rect.h), 0.0f
        };

        glm::mat4 model = glm::mat4(1.0f);
        GLuint colorLoc = glGetUniformLocation(shader->shaderProgram, "Color");
        GLuint projectionLoc = glGetUniformLocation(shader->shaderProgram, "projection");
        GLuint modelLoc = glGetUniformLocation(shader->shaderProgram, "model");

        if(basic_vbo.buffer == 0){
            basic_vbo = VBO(vertices, sizeof(vertices));
        }
        basic_vbo.Update(vertices, sizeof(vertices));
        shader->use();

        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform4f(colorLoc, (GLfloat)color.r/255, (GLfloat)color.g/255, (GLfloat)color.b/255, (GLfloat)color.a/255);

        basic_vao.Bind();
        basic_vao.LinkAttrib(basic_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
}

SDL_Texture* Renderer::createTextureFromSurface(SDL_Surface* surface){
    return SDL_CreateTextureFromSurface(Renderer::renderer, surface);
}

SDL_GLContext Renderer::getGLContext(){
    return glcontext;
}
