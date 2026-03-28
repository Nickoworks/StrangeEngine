#include "Animator.h"

Keyframe::Keyframe(float* values_, float endValues_, int duration_, float increment_) : value(values_), 
endValue(endValues_), 
duration(duration_),
valueIncrement(increment_){
    startValue = *value;
}

Animator::Animator(std::vector<Keyframe> keyframes_) : currenTime(0), 
currFrame(0), keyframes(keyframes_){
    played_once = false;
    for(int i = 0; i < keyframes.size(); i++){
        keyframes[i].startValue = *keyframes[i].value;
    }
    currenTime = 0;
    currFrame = 0;
    frames_is_played = 0;
    currFrameDuration = 0;
}

void Animator::play(){
    startTime = Window::get_ticks();
    currFrameDuration = keyframes[currFrame].duration;
    if(currenTime+currFrameDuration < startTime){
        for(int i = 0; i < keyframes.size(); i++){
            int isEnd = 0;
            for(int k = 0; k < keyframes.size(); k++){
                if(*keyframes[k].value <= keyframes[k].endValue){
                    isEnd++;
                }
            }
            if(isEnd == keyframes.size()){
                for(int j = 0; j < keyframes.size(); j++){
                    *keyframes[j].value = keyframes[j].startValue;
                }
                frames_is_played = 0;
                currFrame = 0; 
                break;
            }
            if(*keyframes[i].value == keyframes[i].endValue){
                continue;
            }
            if(*keyframes[i].value != keyframes[i].endValue){
                (*keyframes[i].value) += keyframes[i].valueIncrement;
            }
        }
        currenTime = startTime;
    }
}

void Animator::play_once(){
    if(!played_once){
        startTime = Window::get_ticks();
        currFrameDuration = keyframes[currFrame].duration;
        if(currenTime+currFrameDuration < startTime){
            for(int i = 0; i < keyframes.size(); i++){
                int isEnd = 0;
                
                for(int k = 0; k < keyframes.size(); k++){
                    if(keyframes[k].valueIncrement < 0){
                        if(*keyframes[k].value <= keyframes[k].endValue){
                            isEnd++;
                        }
                    } else if(keyframes[k].valueIncrement > 0){
                        if(*keyframes[k].value >= keyframes[k].endValue){
                            isEnd++;
                        }
                    }
                }
                if(isEnd == keyframes.size()){
                    played_once = true;
                    frames_is_played = 0;
                    currFrame = 0; 
                    break;
                }
                if(*keyframes[i].value == keyframes[i].endValue){
                    continue;
                }
                if(*keyframes[i].value != keyframes[i].endValue){
                    (*keyframes[i].value) += keyframes[i].valueIncrement;
                }
            }
            currenTime = startTime;
        }
    }
}

void Animator::set_played_once(bool value_){
    played_once = value_;
}

bool Animator::get_played_once(){
    return played_once;
}
