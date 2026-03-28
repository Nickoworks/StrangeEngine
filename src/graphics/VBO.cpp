#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size){   
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::VBO(){}

void VBO::Bind(){
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void VBO::Update(GLfloat* vertices, GLsizeiptr size){
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete(){
    glDeleteBuffers(1, &buffer);
    buffer = 0;
}
