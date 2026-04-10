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
    void use();
    void drawArray();
    
   

};


