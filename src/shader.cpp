#include "shader.hpp"

Shader::Shader(const std::string &pathVertexFile, const std::string &pathFragFile)
{



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

}

void Shader::drawArray()
{
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}


