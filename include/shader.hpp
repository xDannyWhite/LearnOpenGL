#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Shader
{
private:

    const char* vertexSrc;
    const char* fragSrc;
    unsigned int VAO;
    unsigned int VOB;
    

public:
    
    Shader();
    ~Shader();
    
    void initBuffers(float vertices[]);
    void createVertexShader();
    void createFragShader();
};


