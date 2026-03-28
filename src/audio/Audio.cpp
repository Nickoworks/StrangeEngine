#include "Audio.h"

int Audio::master_volume = 128;
int Audio::sound_volume = 128;
int Audio::music_volume = 128;

std::unordered_map<std::string, int> Audio::sounds_channel;
std::unordered_map<std::string, int> Audio::music_channel;

void Audio::trimSpaces(std::string& str) {
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    if(start == std::string::npos){
        str = "";
    } else {
        str = str.substr(start, end - start + 1);
    }
}

void Audio::init(std::string audio_channels_cfg){
    if(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0){
        LOG("AUDIO ERROR", "audio init error", WHITE_RED_CODE);
        return;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
        LOG("AUDIO ERROR", "audio open error", WHITE_RED_CODE);
        return;
    }
    if(Mix_AllocateChannels(MAX_CHANNELS) == -1){
        LOG("AUDIO ERROR", "audio allocation error", WHITE_RED_CODE);
        return;
    }
    _audio_config_parser(audio_channels_cfg);
}

void Audio::_audio_config_parser(std::string data){
    std::istringstream audio_cfg_file(data);
    std::string line;

    while(std::getline(audio_cfg_file, line)){
        if(line.find("//") != std::string::npos && line == ""){
            continue;
        }
        size_t pos = line.find(":");
        std::string channel_name = line.substr(0, pos);
        std::string channel_volume;
        line.erase(0, pos+1);
        channel_volume = line;
        trimSpaces(channel_name);
        trimSpaces(channel_volume);
        try{
            if(channel_name == "master" || channel_name == "MASTER" || channel_name == "Master"){
                set_master_volume(std::stoi(channel_volume));
                continue;
            }
            if(channel_name == "music" || channel_name == "MUSIC" || channel_name == "Music"){
                set_music_volume(std::stoi(channel_volume));
                continue;
            }
            if(channel_name == "sound" || channel_name == "SOUND" || channel_name == "Sound"){
                set_sound_volume(std::stoi(channel_volume));
                continue;
            }
        } catch (const std::invalid_argument& e) {
            LOG("AUDIO ERROR", "invalid arguments!", WHITE_RED_CODE);
        }
    }
}

void Audio::play_sound(std::string name){
    if(sounds_channel.empty()){
        sounds_channel[name] = 0;
        set_sound_volume(sound_volume);
        Mix_PlayChannel(0, ResourceManager::getAudio(name), 0);
        return;
    }
    int maxChannel = 0;
    for(auto& pair : sounds_channel){
        if(pair.second > maxChannel){
            maxChannel++;
        }
    }
    if(maxChannel+1 > MAX_CHANNELS){
        clear_sound_channels();
        sounds_channel[name] = 0;
        Mix_PlayChannel(0, ResourceManager::getAudio(name), 0);
        return;
    }
    sounds_channel[name] = maxChannel + 1;
    set_sound_volume(sound_volume);
    Mix_PlayChannel(maxChannel + 1, ResourceManager::getAudio(name), 0);
}

void Audio::play_sound_loop(std::string name){
    if(sounds_channel.empty()){
        sounds_channel[name] = 0;
        set_sound_volume(sound_volume);
        Mix_PlayChannel(0, ResourceManager::getAudio(name), 0);
        return;
    }
    int maxChannel = 0;
    for(auto& pair : sounds_channel){
        if(pair.second > maxChannel){
            maxChannel++;
        }
    }
    if(maxChannel+1 > MAX_CHANNELS){
        clear_sound_channels();
        sounds_channel[name] = 0;
        Mix_PlayChannel(0, ResourceManager::getAudio(name), 0);
        return;
    }
    sounds_channel[name] = maxChannel + 1;
    set_sound_volume(sound_volume);
    Mix_PlayChannel(maxChannel + 1, ResourceManager::getAudio(name), -1);
}

void Audio::play_music(std::string name){
    if(music_channel.empty()){
        music_channel[name] = 0;
        set_music_volume(music_volume);
        Mix_PlayChannel(0, ResourceManager::getAudio(name), 0);
        return;
    }
    int maxChannel = 0;
    for(auto& pair : music_channel){
        if(pair.second > maxChannel){
            maxChannel++;
        }
    }
    if(maxChannel+1 > MAX_CHANNELS){
        music_channel[name] = 0;
        Mix_PlayChannel(0, ResourceManager::getAudio(name), 0);
        return;
    }
    music_channel[name] = maxChannel + 1;
    set_music_volume(music_volume);
    Mix_PlayChannel(maxChannel + 1, ResourceManager::getAudio(name), 0);
}

void Audio::play_music_loop(std::string name){
    if(music_channel.empty()){
        music_channel[name] = 0;
        set_music_volume(music_volume);
        Mix_PlayChannel(0, ResourceManager::getAudio(name), 0);
        return;
    }
    int maxChannel = 0;
    for(auto& pair : music_channel){
        if(pair.second > maxChannel){
            maxChannel++;
        }
    }
    if(maxChannel+1 > MAX_CHANNELS){
        music_channel[name] = 0;
        Mix_PlayChannel(0, ResourceManager::getAudio(name), 0);
        return;
    }
    music_channel[name] = maxChannel + 1;
    set_music_volume(music_volume);
    Mix_PlayChannel(maxChannel + 1, ResourceManager::getAudio(name), -1);
}

bool Audio::is_playing_sound(std::string name){
    return Mix_Playing(sounds_channel[name]);
}

bool Audio::is_playing_music(std::string name){
    return Mix_Playing(music_channel[name]);
}

void Audio::set_master_volume(int volume){
    master_volume = volume;
    Mix_Volume(-1, master_volume);
}

void Audio::set_sound_volume(int volume){
    sound_volume = volume;
    for(auto& pair : sounds_channel){
        Mix_Volume(pair.second, sound_volume);
    }
}

void Audio::set_music_volume(int volume){
    music_volume = volume;
    for(auto& pair : music_channel){
        Mix_Volume(pair.second, sound_volume);
    }
}

void Audio::clear_sound_channels(){
    sounds_channel.clear();
}

void Audio::clear_music_channels(){
    music_channel.clear(); 
}

void Audio::close_audio(){
    Mix_CloseAudio();
}
