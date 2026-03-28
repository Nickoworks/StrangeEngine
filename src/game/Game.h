#pragma once
#include <iostream>
#include "SDL_include.h"
#include "SDL_image_include.h"
#include "SDL_ttf_include.h"
#include "SDL_mixer_include.h"

#include "OpenGL_include.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "VBO.h"
#include "VAO.h"

#include <sstream>
#include <vector>
#include "Window.h"
#include "Renderer.h"
#include "Events.h"
#include "Texture.h"
#include "AnimatedSprite.h"
#include "Tilemap.h"
#include "Text.h"
#include "Entity.h"
#include "Player.h"
#include "Camera.h"
#include "CollisionKit.h"
#include "HitBoxes.h"
#include "UI.h"
#include "load_dialog.h"
#include "TextBox.h"
#include "Object.h"
#include "constants.h"
#include "Colors.h"
#include "ResourceManager.h"
#include "EntityManager.h"
#include "ObjectManager.h"
#include "ScriptRegistry.h"
#include "scripts.h"
#include "Scene.h"
#include "BlockTilemap.h"
#include "Logger.h"
#include "Engine.h"
#include "devscripts.h"
#include <cstdlib>
#include <ctime>

#include "load_file.h"

class Game{
public:
    static float currentFPS;
    static float deltaTime;
    static bool running;
    static std::string assets_path_sprites;
    static std::string assets_path_tile_sets;
    static std::string assets_path_mus;
    static std::string assets_path_level_files;
    static int startFrame;
    void game_loop(void);
};
