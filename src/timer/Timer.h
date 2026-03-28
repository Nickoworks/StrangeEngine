#pragma once
#include "Window.h"
#include <iostream>

class Timer{
    bool timeIsElapsed;
    unsigned int startTime;
    unsigned int remainingTime;
    unsigned int timerCountDown;

public:
    Timer(int time_remaining);

    void update();
    void start();
    int getTimeLeft();
    bool isFinished();
};
