#pragma once

#ifdef _WIN32
    #include <GL/glew.h>
#elif __linux__
    #include <GL/glew.h>
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        #include <GL/glew.h>
    #elif TARGET_OS_IOS
        #include <OpenGLES/ES3/gl.h>
    #endif
#else
    #error "Unsupported platform"
#endif