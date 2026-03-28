#include "engine/Engine.h"

#if defined(__APPLE__) || defined(__linux__)
int main(int argc, char* argv[]){
    Engine::init();
    Engine::process();

    return 0;
}
#elif defined(_WIN32)
int WinMain(){
    Engine::init();
    Engine::process();

    return 0;
}
#else
#error "Unsupporting platform"
#endif
