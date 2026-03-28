#pragma once
#include "OpenGL_include.h"

class VBO{
public:
    GLuint buffer;
    VBO(GLfloat* vertices, GLsizeiptr size);
    VBO();

    void Bind();
    void Update(GLfloat* vertices, GLsizeiptr size);
    void Unbind();
    void Delete();
};
