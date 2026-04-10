#include "shader.hpp"

Shader::Shader(float vertices[], const std::string &pathVertexFile, const std::string &pathFragFile)
{
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VOB);
    glBindBuffer(GL_ARRAY_BUFFER, VOB);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    std::string vertexCode = Assetmanager::LoadFile(pathVertexFile);
    const char* vertexSrc = vertexCode.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrc, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[1024];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error: SHADER::VERTX compilation failed!" << infoLog << std::endl;
    }
    
    std::string fragmentCode = Assetmanager::LoadFile(pathFragFile);
    const char* fragmentSrc = fragmentCode.c_str();

    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragmentSrc, NULL);
    glCompileShader(fragShader);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragShader,512,NULL, infoLog);
        std::cout << "Error: SHADER::FRAG compilation failed!" << infoLog << std::endl;

    }

    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragShader);
    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderID,512,NULL, infoLog);
    }
    

}

void Shader::use()
{
    glUseProgram(shaderID);
    glBindVertexArray(VAO);
}

void Shader::drawArray()
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

Shader::~Shader()
{
}
