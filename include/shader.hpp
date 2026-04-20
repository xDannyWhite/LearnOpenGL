#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "Assetmanager.hpp"

class Shader
{
private:
    
    unsigned int shaderID;
    

public:
    
    Shader(const std::string &pathVertexFile, const std::string &pathFragFile );
    unsigned int getShaderID();
    void use();
    void drawArray();
    void drawElement();
    void setUniformFloat(const char* UniformName, float a);

};


