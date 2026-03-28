#pragma once
#include <iostream>
#include "SDL_include.h"
#include "SDL_mixer_include.h"
#include <unordered_map>
#include <sstream>
#include "Logger.h"
#include "ResourceManager.h"
#include "constants.h"

class Audio{
public: 
    static int master_volume;
    static int sound_volume;
    static int music_volume;

    static std::unordered_map<std::string, int> sounds_channel;
    static std::unordered_map<std::string, int> music_channel;

    static void init(std::string audio_channels_cfg);
    static void trimSpaces(std::string& str);
    static void _audio_config_parser(std::string data);
    static void play_sound(std::string name);
    static void play_sound_loop(std::string name);
    static void play_music(std::string name);
    static void play_music_loop(std::string name);
    static bool is_playing_sound(std::string name);
    static bool is_playing_music(std::string name);
    static void set_master_volume(int volume);
    static void set_sound_volume(int volume);
    static void set_music_volume(int volume);

    static void clear_sound_channels();
    static void clear_music_channels();
    static void close_audio();
};
