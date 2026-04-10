#include "shader.hpp"

Shader::Shader()
{
  
}

void Shader::initBuffers(float vertices[])
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VOB);
    glBindBuffer(GL_ARRAY_BUFFER, VOB);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
}
