#pragma once

#include "OpenGL_include.h"
#include <unordered_map>
#include <iostream>
#include "Logger.h"
#include "Preloader.h"

GLuint compileShader(std::string source, GLenum shaderType);

class ShaderProgram{
public:
    std::unordered_map<std::string, GLuint> uniformLocations;
    GLuint shaderProgram;
    ShaderProgram();
    ShaderProgram(std::string frag_path, std::string vert_path);
    void addUniform(std::string name, GLuint uniform);
    void setUniforms(std::unordered_map<std::string, GLuint> uniforms);
    ~ShaderProgram();

    void use();
};
