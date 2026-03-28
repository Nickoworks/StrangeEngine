#ifndef EVENTS
#define EVENTS
#include "SDL_include.h"
#include "Preloader.h"
#include "ScriptRegistry.h"
#include <iostream>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <vector>


class Events{
public:
    static SDL_Event events;
    static const Uint8* currentKeyState;

    enum class KeyState{
        PRESS,
        RELEASE,
        HOLD
    };

    static int initialise(std::string signal_path);

    static void _parseSignals(std::string file);
    static void runScripts();
    static bool isKeyPressed(SDL_Scancode key);
    static bool isKeyHeld(SDL_Scancode key);
    static bool isKeyReleased(SDL_Scancode key);
    
    static void pollEvents(bool &running);

    static void connectToSignal(std::string signal_name, std::string func_name);
    static void disconnectSignal(std::string signal_name);
    static void emitSignal(std::string signal_name);
    static bool getSignalState(std::string name);

    static std::unordered_map<std::string, bool> signals;
    static std::unordered_map<std::string, std::string> slots;
    
    static std::unordered_map<int, KeyState> keyState;
};
#endif