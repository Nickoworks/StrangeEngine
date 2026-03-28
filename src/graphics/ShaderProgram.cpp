#include "ShaderProgram.h"

GLuint compileShader(std::string source, GLenum shaderType){
    GLuint shader = glCreateShader(shaderType);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        LOG("SHADER COMPILE ERROR", std::string(infoLog), RED_CODE);
    } else {
        if(shaderType == GL_VERTEX_SHADER){
            LOG("SHADER COMPILER", "Vertex shader is compiled", GREEN_CODE);
        } else if(shaderType == GL_FRAGMENT_SHADER){
            LOG("SHADER COMPILER", "Fragment shader is compiled", GREEN_CODE);
        }
    }
    return shader;
}

ShaderProgram::ShaderProgram(){}

ShaderProgram::ShaderProgram(std::string frag_path, std::string vert_path){
    std::string vert_src = Preloader::load_file(vert_path);
    std::string frag_src = Preloader::load_file(frag_path);

    GLuint vertexShader = compileShader(vert_src, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(frag_src, GL_FRAGMENT_SHADER);

    shaderProgram = glCreateProgram();
    // shaderProgram = glCreateProgram();

    if(shaderProgram == 0){
        LOG("SHADER PROGRAM", "Failed to create program!", RED_CODE);
        return;
    }

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        LOG("SHADER PROGRAM", "Shader program linking error: " + std::string(infoLog), RED_CODE);
    } else {
        LOG("SHADER PROGRAM", "Shader program is linked", GREEN_CODE);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(shaderProgram);
}

void ShaderProgram::use(){
    glUseProgram(shaderProgram);
}

void ShaderProgram::addUniform(std::string name, GLuint uniform){
    uniformLocations[name] = uniform;
}

void ShaderProgram::setUniforms(std::unordered_map<std::string, GLuint> uniforms){
    uniformLocations = uniforms;
}
