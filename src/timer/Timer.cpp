#include "Timer.h"

Timer::Timer(int time_remaining) : remainingTime(time_remaining), 
timeIsElapsed(false),
startTime(0), 
timerCountDown(time_remaining){
}

void Timer::start(){
    startTime = Window::get_ticks();
    timeIsElapsed = false;
}

void Timer::update(){
    if(!timeIsElapsed){
        int elapsedTime = Window::get_ticks() - startTime;
        if(elapsedTime > timerCountDown){
            timeIsElapsed = true;
        }
    }
}

int Timer::getTimeLeft(){
    if(timeIsElapsed){
        return 0;
    }
    int elapsedTime = Window::get_ticks() - startTime;
    return timerCountDown - elapsedTime;
}

bool Timer::isFinished(){
    return timeIsElapsed;
}
