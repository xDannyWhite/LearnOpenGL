#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include "shader.hpp"






void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void proccesInput(GLFWwindow* window);
std::string LoadFile(const std::string &path);


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
    

    //creating VertexBufferObject and VertexArrayObject and binding them
    //creating Shader frag and vert files. Read them convert into string and than convert into const char* to load file for the shaderpogramm creation.
    unsigned int VAO;
    glGenVertexArrays(1, &VAO); 
    glBindVertexArray(VAO);

    unsigned int VOB;
    glGenBuffers(1, &VOB);
    glBindBuffer(GL_ARRAY_BUFFER, VOB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    std::string vertxCode = LoadFile("shaders/traiangle.vert");
    const char* vertxSrc = vertxCode.c_str();
    

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1, &vertxSrc,NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &success);
    
    //Checking if not loaded successfully.
    if (!success)
    {
        glGetShaderInfoLog(vertexShader,512,NULL, infoLog);
        std::cout << "Error: SHADER::VERTX compilation failed!" << infoLog << std::endl;
    }


    std::string fragCode = LoadFile("shaders/color.frag");
    const char* fragSrc = fragCode.c_str();
    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSrc, NULL);
    glCompileShader(fragShader);

  
    glGetShaderiv(fragShader,GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragShader,512,NULL, infoLog);
        std::cout << "Error: SHADER::FRAG compilation failed!" << infoLog << std::endl;

    }
    
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram,512,NULL, infoLog);
    }
    
  // Deleting cause after binding and linking dont need anymore.
  
    


    
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    while (!glfwWindowShouldClose(window))
    {
        proccesInput(window);
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0, 3);
  
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

std::string LoadFile(const std::string &path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
