cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME game)
project(${PROJECT_NAME})
add_subdirectory(thirdparty/tinyxml2)
add_subdirectory(thirdparty/json)
include_directories(thirdparty/imgui)

add_compile_options(-ferror-limit=100)

file(GLOB IMGUI_FILES_CPP "thirdparty/imgui/*.cpp")
file(GLOB IMGUI_FILES_H "thirdparty/imgui/*.h")

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "$${CMAKE_CXX_FLAGS} -fsanitize=address -g")
endif()

add_executable(${PROJECT_NAME} src/main.cpp)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    target_compile_options(${PROJECT_NAME} PRIVATE -mwindows)
endif()

if(APPLE OR UNIX)
    find_library(SDL2_LIBRARY SDL2)
    find_library(SDL2_IMAGE_LIBRARY SDL2_image)
    find_library(SDL2_TTF_LIBRARY SDL2_ttf)
    find_library(SDL2_MIXER_LIBRARY SDL2_mixer)
    find_library(GLEW_LIBRARY GLEW)
    find_path(GLEW_INCLUDE_DIR GL/glew.h)

    find_package(OpenGL REQUIRED)
    find_package(GLM REQUIRED)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${SDL2_MIXER_LIBRARY}
        ${GLEW_LIBRARY}
        OpenGL::GL
        glm::glm
        tinyxml2
        nlohmann_json
    )
    # include_directories($(GLM_INLCUDE_DIRS))
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIR})
elseif(WIN32)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_mixer::SDL2_mixer
        SDL2_ttf::SDL2_ttf
    )
endif()

file(GLOB_RECURSE HEADER_DIRS RELATIVE ${CMAKE_SOURCE_DIR} src/*)

foreach(dir ${HEADER_DIRS})
    get_filename_component(dir ${dir} DIRECTORY)
    include_directories(${CMAKE_SOURCE_DIR}/${dir})
endforeach()

include_directories(src/include)

target_sources(${PROJECT_NAME} PRIVATE
   ${IMGUI_FILES_CPP}
   ${IMGUI_FILES_H}
   thirdparty/imgui/backends/imgui_impl_sdl2.h
   thirdparty/imgui/backends/imgui_impl_sdl2.cpp
   thirdparty/imgui/backends/imgui_impl_opengl3_loader.h
   thirdparty/imgui/backends/imgui_impl_opengl3.h
   thirdparty/imgui/backends/imgui_impl_opengl3.cpp
   thirdparty/imguiTextEditor/TextEditor.h
   thirdparty/imguiTextEditor/TextEditor.cpp
#    thirdparty/imgui/backends/imgui_impl_sdlrenderer2.h
#    thirdparty/imgui/backends/imgui_impl_sdlrenderer2.cpp
   src/events/Events.cpp
   src/events/Events.h
   src/renderer/Renderer.cpp
   src/renderer/Renderer.h
#    src/renderer/ConfiguredSprite.h
#    src/renderer/ConfiguredSprite.cpp
   src/window/Window.cpp
   src/window/Window.h 
   src/graphics/Texture.cpp
   src/graphics/Texture.h
   src/tilemap/Tilemap.cpp
   src/tilemap/Tilemap.h
   src/tilemap/TilemapLayer.h
   src/tilemap/TilemapLayer.cpp
   src/utils/loaders/load_file.cpp
   src/utils/loaders/load_file.h
   src/game/Game.cpp
   src/game/Game.h
   src/text/Text.cpp
   src/text/Text.h
   src/game/gameObjects/entities/Entity.cpp
   src/game/gameObjects/entities/Entity.h
   src/game/gameObjects/player/Player.cpp
   src/game/gameObjects/player/Player.h
   src/game/gameObjects/GameObject.h
   src/animation/AnimatedSprite.cpp
   src/animation/AnimatedSprite.h
   src/animation/Animator.h
   src/animation/Animator.cpp
   src/game/gameObjects/player/Camera.cpp
   src/game/gameObjects/player/Camera.h
   src/game/collisionKit/CollisionKit.cpp
   src/game/collisionKit/CollisionKit.h
   src/game/gameObjects/objects/Object.cpp
   src/game/gameObjects/objects/Object.h
   src/UI/textBox/TextBox.h
   src/UI/textBox/TextBox.cpp
   src/UI/UI.h
   src/UI/UI.cpp
   src/utils/loaders/load_dialog.h
   src/utils/loaders/load_dialog.cpp
   src/tilemap/BlockTilemap.h
   src/tilemap/BlockTilemap.cpp 
   src/constants.h
   src/graphics/Colors.h
   src/graphics/VFX.h
   src/graphics/VFX.cpp
   src/preloader/Preloader.h
   src/preloader/Preloader.cpp
   src/resourceManager/ResourceManager.h
   src/resourceManager/ResourceManager.cpp
   src/scriptRegistry/ScriptRegistry.h
   src/scriptRegistry/ScriptRegistry.cpp
   src/managers/EntityManager.h
   src/managers/EntityManager.cpp
   src/managers/ObjectManager.h
   src/managers/ObjectManager.cpp
   src/game/collisionKit/HitBoxes.h
   src/game/collisionKit/HitBoxes.cpp
   src/scene/Scene.h
   src/scene/Scene.cpp
   src/scripts/scripts.h
   src/scripts/script.cpp
   src/managers/PlayerManager.h
   src/managers/PlayerManager.cpp
   src/managers/TilemapManager.h
   src/managers/TilemapManager.cpp
   src/utils/Vector2D/Vector2D.h
   src/timer/Timer.h
   src/timer/Timer.cpp
   src/engine/Logger.h
   src/engine/Logger.cpp
   src/engine/Engine.h
   src/engine/Engine.cpp
   src/engine/HardwareInfo.h
   src/engine/HardwareInfo.cpp
   src/managers/AnimManager.h
   src/managers/AnimManager.cpp
   src/audio/Audio.h
   src/audio/Audio.cpp
   src/physics/Physics.h
   src/physics/Physics.cpp
   src/scripts/devscripts.h
   src/scripts/devscripts.cpp
   src/graphics/ShaderProgram.h
   src/graphics/ShaderProgram.cpp
   src/graphics/ShaderManager.h
   src/graphics/ShaderManager.cpp
   src/graphics/VBO.h
   src/graphics/VBO.cpp
   src/graphics/VAO.h
   src/graphics/VAO.cpp
)
