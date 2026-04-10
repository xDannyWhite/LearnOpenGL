#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include "shader.hpp"






void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void proccesInput(GLFWwindow* window);



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

    // create Vertices float array and store the shape in Normalized Device Coordinates (NDC)

    float vertices[] = {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.0f, 0.5f , 0.0f
    };
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VOB;
    glGenBuffers(1, &VOB);
    glBindBuffer(GL_ARRAY_BUFFER, VOB);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
  
    Shader traiangle("shaders/traiangle.vert", "shaders/color.frag");
    


    
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    while (!glfwWindowShouldClose(window))
    {
        proccesInput(window);
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        traiangle.use();
        glBindVertexArray(VAO);
        traiangle.drawArray();
     
  
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

void proccesInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    

}

