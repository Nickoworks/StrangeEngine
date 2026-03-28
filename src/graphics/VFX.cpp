#include "VFX.h"

VAO VFX::vfx_vao(1);
VBO VFX::vfx_vbo;

void VFX::init(){
    vfx_vao = VAO();
    LOG("VFX", "inited");
}

void VFX::delete_buffers(){
    GLint currBuffer = 0;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currBuffer);
    if(currBuffer == vfx_vao.buffer){
        vfx_vao.Unbind();
    }
    if(currBuffer == vfx_vbo.buffer){
        vfx_vbo.Unbind();
    }
    vfx_vao.Delete();
    vfx_vbo.Delete();
}

VFX::Vingette::Vingette(Texture* texture) : texture(texture){
}

void VFX::Vingette::draw(){
    Renderer::drawTexture(texture);
}

VFX::Particles::Particles(Texture* texture, 
Vector2D<float> velocity,
SDL_Rect emit_rect,
float lifespan, 
int maxParticles,
int emit_duration, bool visible = true, bool is_emited = true) : texture(texture),
velocity(velocity),
emit_rect(emit_rect),
lifespan(lifespan),
maxParticles(maxParticles),
emit_duration(emit_duration),
frame_last_change(0), visible(visible), is_emited(is_emited){
    particles.reserve(maxParticles);
}

VFX::Particles::Particles(SDL_Color color, 
Vector2D<float> velocity,
SDL_Rect emit_rect,
int w,
int h,
float lifespan, 
int maxParticles,
int emit_duration, bool visible = true, bool is_emited = true) : color(color),
velocity(velocity),
emit_rect(emit_rect),
w(w),
h(h),
lifespan(lifespan),
maxParticles(maxParticles),
emit_duration(emit_duration),
frame_last_change(0), visible(visible), is_emited(is_emited){
    particles.reserve(maxParticles);
}

void VFX::Particles::emit(){
    if(is_emited && visible){
        int time = Window::get_ticks();
        if(particles.size() < maxParticles && frame_last_change + emit_duration < time){
            Particle p = {Vector2D(emit_rect.x + std::rand() %  emit_rect.w, emit_rect.y + std::rand() %  emit_rect.h), 
            velocity, 
            static_cast<float>(lifespan), 
            0.0f, 
            color, 
            w, 
            h};
            particles.push_back(p);
            frame_last_change = time;
        }
    }
}

void VFX::Particles::update(){
    if(visible){
        for(int i = 0; i < particles.size();){
            if(particles[i].age == lifespan){
                particles.erase(particles.begin() + i);
                continue;
            } else if(particles[i].age != lifespan){
                particles[i].position = particles[i].position + particles[i].velocity;
                particles[i].age += 1;
                i++;
            }
        }
        if(texture != nullptr){
            for(int i = 0; i < particles.size(); i++){
                Renderer::drawTexture(texture, 
                                        {static_cast<int>(particles[i].position.x),
                                        static_cast<int>(particles[i].position.y),
                                        static_cast<int>(texture->getWidth()*texture->getScale()), 
                                        static_cast<int>(texture->getHeight()*texture->getScale())});
            }
        } else {
            for(int i = 0; i < particles.size(); i++){
                Renderer::drawFillRect({static_cast<int>(particles[i].position.x), 
                                        static_cast<int>(particles[i].position.y), 
                                        static_cast<int>(particles[i].w), 
                                        static_cast<int>(particles[i].h)}, 
                                        particles[i].color);
            }
        }
    }
}

VFX::Light::Light(Vector2D<int> pos_,
float intencity_,
float size_,
float centralOpacity_,
float distance_,
int shapeType_,
Vector2D<float> shapeTransform_,
Color startColor_, Color glowColor_) : pos(pos_),
intencity(intencity_),
size(size_),
centralOpacity(centralOpacity_),
distance(distance_),
shapeType(shapeType_),
shapeTransform(shapeTransform_),
startColor(startColor_),
glowColor(glowColor_){}

void VFX::Light::draw(){
    ShaderProgram* light_program = ShaderManager::getShader("light");

    glm::mat4 model = glm::mat4(1.0f);

    GLuint projectionLoc = glGetUniformLocation(light_program->shaderProgram, "projection");
    GLuint modelLoc = glGetUniformLocation(light_program->shaderProgram, "model");
    GLuint resolution = glGetUniformLocation(light_program->shaderProgram, "resolution");

    GLuint coordsLoc = glGetUniformLocation(light_program->shaderProgram, "sdlCoords");
    GLuint intencityLoc = glGetUniformLocation(light_program->shaderProgram, "intencity");
    GLuint sizeLoc = glGetUniformLocation(light_program->shaderProgram, "size");
    GLuint startColorLoc = glGetUniformLocation(light_program->shaderProgram, "startColor");
    GLuint glowColorLoc = glGetUniformLocation(light_program->shaderProgram, "glowColor");   
    GLuint centralOpacityLoc = glGetUniformLocation(light_program->shaderProgram, "centralOpacity");
    GLuint shapeTypeLoc = glGetUniformLocation(light_program->shaderProgram, "shapeType");
    GLuint shapeTransformLoc = glGetUniformLocation(light_program->shaderProgram, "shapeTransform");
    GLuint distanceLoc = glGetUniformLocation(light_program->shaderProgram, "distance");
    GLuint lightDirLoc = glGetUniformLocation(light_program->shaderProgram, "lightDir");

    float vertices[] = {
        0.0f, 0.0f, 0.0f,
        float(WINDOW_WIDTH), 0.0f, 0.0f,
        float(WINDOW_WIDTH), float(WINDOW_HEIGHT), 0.0f,
        0.0f, float(WINDOW_HEIGHT), 0.0f
    };

    if(vfx_vbo.buffer == 0){
        vfx_vbo = VBO(vertices, sizeof(vertices));  
    }
    vfx_vbo.Update(vertices, sizeof(vertices));
     
    light_program->use();
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(Renderer::projection));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniform2f(resolution, WINDOW_WIDTH, WINDOW_HEIGHT);
    glUniform2f(coordsLoc, pos.x, pos.y);
    glUniform1f(intencityLoc, intencity);
    glUniform1f(sizeLoc, size);
    glUniform4f(startColorLoc, (float)startColor.r/255, (float)startColor.g/255, (float)startColor.b/255, (float)startColor.a/255); 
    glUniform4f(glowColorLoc, (float)glowColor.r/255, (float)glowColor.g/255, (float)glowColor.b/255, (float)glowColor.a/255); 
    glUniform1f(centralOpacityLoc, centralOpacity);
    glUniform1i(shapeTypeLoc, shapeType);
    glUniform2f(shapeTransformLoc, shapeTransform.x, shapeTransform.y);
    glUniform1f(distanceLoc, distance);
    glUniform2f(lightDirLoc, 0.0f, 0.0f);

    vfx_vao.Bind();
    vfx_vao.LinkAttrib(vfx_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
