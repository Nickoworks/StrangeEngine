#include "devscripts.h"

void devscript_fps(int fps){
    static Text text_fps("FPS: " + std::to_string(fps), 0, 0, 1, ResourceManager::getFont("Fixedsys62.ttf"), WHITE);
    text_fps.change_text("FPS: " + std::to_string(fps));
    text_fps.draw();
}
