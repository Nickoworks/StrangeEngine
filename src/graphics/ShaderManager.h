#pragma once
#include <iostream>
#include <unordered_map>
#include <filesystem>
#include <memory>
#include "OpenGL_include.h"
#include "ShaderProgram.h"
#include "Preloader.h"
#include <vector>

class ShaderManager{
public:
    static std::string currUseShader;
    static std::unordered_map<std::string, std::shared_ptr<ShaderProgram> > shaders;
    static void init(std::string shaderDirPath);
    static void useShader(std::string shaderName);
    static ShaderProgram* getCurrShader();
    static ShaderProgram* getShader(std::string shaderName);
    static void deleteAllShaders();
};
