#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 WorldPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    WorldPos = vec3(model * vec4(aPosition, 1.0));
    Normal = aNormal;
    TexCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}