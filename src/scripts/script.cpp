#include "scripts.h"

// animation_frames = anim_component[0];
// start_animation_frame = anim_component[1];
// animation_index = anim_component[2];
// frame_per_milsec = anim_component[3];
// current_frame = anim_component[4];
// frame_last_change = anim_component[5];


void script(){

}


void regScripts(){
    ScriptRegistry::registerScript("script", script);
}
