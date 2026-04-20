#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include "shader.hpp"
#include "stb_image.h"






void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void proccesInput(GLFWwindow* window,float &x, float &y);



int main ()
{
    
    //INIT GLFW and set version and coreprofil
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL",NULL ,NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Create Context and check if glad is propably loaded.
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD\n";
        return -1;
    }
    glEnable(GL_BLEND);
    glad_glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // create Vertices float array and store the shape in Normalized Device Coordinates (NDC)

    float vertices[] = {
    //Vertices              
     0.5f,  0.5f, 0.0f,         1.0f, 0.0f, 0.0f,       1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,         0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,         0.0f, 0.0f, 1.0f,       0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,         1.0f, 1.0f, 0.0,        0.0f, 1.0f
    };
   
    float textCords[] = {
        
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f

    };

    unsigned int indices[] {
        0, 1, 3,
        1, 2, 3
    };

    float xOffset, yOffset = 0.0f;
    

    unsigned int VAO, VOB, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    glGenBuffers(1, &VOB);
    glBindBuffer(GL_ARRAY_BUFFER, VOB);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);
  

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8* sizeof(float),(void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int texture;
    glGenBuffers(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannel;
    unsigned char* data = stbi_load("assets/player.png", &width, &height, &nrChannel, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture\n";
    }

    stbi_image_free(data);

    





    Shader traiangle("shaders/traiangle.vert", "shaders/color.frag");

    traiangle.use();
    glUniform1i(glGetUniformLocation(traiangle.getShaderID(),"ourTextur"), 0);
   
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    while (!glfwWindowShouldClose(window))
    {
        proccesInput(window,xOffset,yOffset);
        glClearColor(0.0f,1.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        traiangle.use();
        traiangle.setUniformFloat("xOffset",xOffset);
        traiangle.setUniformFloat("yOffset",yOffset);        
  
        glBindVertexArray(VAO);
        traiangle.drawElement();

        
       
     
  
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0,0,width,height);
}

void proccesInput(GLFWwindow *window, float &x, float &y)
{
    if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
    {
        y += 0.01f;
    }
    
    if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
    {
        y -= 0.01f;
    }
    
    if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
    {
        x -= 0.01f;
    }

    if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
    {
        x += 0.01f;
    }

}

