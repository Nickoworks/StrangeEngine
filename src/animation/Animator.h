#pragma once
#include <iostream>
#include <vector>
#include "Window.h"

struct Keyframe{
public:
    float* value;
    float endValue;
    float startValue;
    int duration;
    float valueIncrement;
    Keyframe(float* value_, float endValue_, int duration_, float increment_);
};

class Animator{
    bool played_once;
    int currenTime;
    int startTime;
    int currFrameDuration;
    int currFrame;

    int frames_is_played;
    std::vector<Keyframe> keyframes;

public:
    Animator(std::vector<Keyframe> keyframes_);
    void play();
    void play_once();
    void set_played_once(bool value_);
    bool get_played_once();
};