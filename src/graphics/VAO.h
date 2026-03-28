#pragma once
#include "OpenGL_include.h"
#include "VBO.h"

class VAO{
public:
    GLuint buffer;

    VAO(int i);
    VAO();

    void LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
    void Delete();
};
