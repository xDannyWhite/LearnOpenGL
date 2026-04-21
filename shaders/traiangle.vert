#version 330 core 
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCord;

out vec3 vertexColor;
out vec2 TextCord;

uniform float xOffset;
uniform float yOffset;
uniform mat4 model;

void main()
{
    gl_Position = model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = aColor;
    TextCord = aTextCord;
}