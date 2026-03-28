#pragma once

#ifdef _WIN32
    #include "imgui.h"
    #include "../../thirdparty/imgui/backends/imgui_impl_sdl2.h"
    #include "../../thirdparty/imgui/backends/imgui_impl_opengl3.h"
    #include "../../thirdparty/imguiTextEditor/TextEditor.h"
#elif __linux__
    #include "imgui.h"
    #include "../../thirdparty/imgui/backends/imgui_impl_sdl2.h"
    #include "../../thirdparty/imgui/backends/imgui_impl_opengl3.h"
    #include "../../thirdparty/imguiTextEditor/TextEditor.h"
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        #include "imgui.h"
        #include "../../thirdparty/imgui/backends/imgui_impl_sdl2.h"
        #include "../../thirdparty/imgui/backends/imgui_impl_opengl3.h"
        #include "../../thirdparty/imguiTextEditor/TextEditor.h"
    #elif TARGET_OS_IOS
        #include "imgui.hpp"
        #include "imgui_impl_sdl2.hpp"
        #include "imgui_impl_opengl3.hpp"
        #include "TextEditor.hpp"
    #endif
#else
    #error "Unsupported platform"
#endif