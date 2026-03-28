#include "Events.h"
#include <string.h>
#include "SDL_include.h"
#include "Window.h"
#include "Renderer.h"
#include <iostream>
#include "Tilemap.h"

SDL_Event Events::events;
const Uint8* Events::currentKeyState = SDL_GetKeyboardState(NULL);

std::unordered_map<int, Events::KeyState> Events::keyState;
std::unordered_map<std::string, bool> Events::signals;
std::unordered_map<std::string, std::string> Events::slots;

int Events::initialise(std::string signal_path){
    for(int i = 0; i < SDL_NUM_SCANCODES; i++){
        keyState[i] = KeyState::RELEASE;
    }
    _parseSignals(Preloader::load_file(signal_path));
    return 0;
}

void Events::_parseSignals(std::string file){
    std::istringstream signalsFile(file);
    std::string line;

    while(std::getline(signalsFile, line)){
        if(line == ""){
            continue;
        } else if(line.find("//") != std::string::npos){
            continue;
        }
        size_t pos = line.find(":");
        std::string name = line.substr(0, pos);
        std::string slot;
        line.erase(0, pos+1);
        signals[name] = false;
        if(line == "null" || line == "NULL"){
            continue;
        }
        slots[name] = line;      
    }   
}

bool Events::isKeyPressed(SDL_Scancode key){
    return keyState[static_cast<int>(key)] == KeyState::PRESS;
}

bool Events::isKeyHeld(SDL_Scancode key){
    return keyState[static_cast<int>(key)] == KeyState::HOLD;
}

bool Events::isKeyReleased(SDL_Scancode key){
    return keyState[static_cast<int>(key)] == KeyState::RELEASE;
}

void Events::connectToSignal(std::string signal_name, std::string func_name){
    slots[signal_name] = func_name;
}

void Events::disconnectSignal(std::string signal_name){
    slots.erase(signal_name);
}

void Events::emitSignal(std::string name){
    signals[name] = true;
}

bool Events::getSignalState(std::string name){
    return signals[name];    
}   

void Events::runScripts(){
    for(auto& pair : slots){
        if(signals[pair.first] == true){
            ScriptRegistry::runScript(pair.second);
        }
    }
}

void Events::pollEvents(bool &running){
    SDL_PollEvent(&Events::events);
    if(Events::events.type == SDL_QUIT) { running = false; }
    const Uint8* currKeyState = SDL_GetKeyboardState(nullptr);
    
    for(int i = 0; i < SDL_NUM_SCANCODES; i++){
        bool isPressed = currKeyState[i] == 1;

        if(isPressed && keyState[i] == KeyState::RELEASE){
            keyState[i] = KeyState::PRESS;
        } else if(!isPressed && keyState[i] == KeyState::HOLD){
            keyState[i] = KeyState::RELEASE;
        } else if(isPressed && keyState[i] == KeyState::PRESS){
            keyState[i] = KeyState::HOLD;
        }
    }

    runScripts();
    for(auto& pair : signals){
        pair.second = false;
    }
}
