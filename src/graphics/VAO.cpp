#include "VAO.h"

VAO::VAO(int i){

}

VAO::VAO(){
    glGenVertexArrays(1, &buffer);
}

void VAO::LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset){
    vbo.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.Unbind();
}   

void VAO::Bind(){
    glBindVertexArray(buffer);
}

void VAO::Unbind(){
    glBindVertexArray(0);
}   

void VAO::Delete(){
    glDeleteVertexArrays(1, &buffer);
}
