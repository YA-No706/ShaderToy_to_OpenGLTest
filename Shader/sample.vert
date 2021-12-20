#version 460 core

layout (location = 0) in vec3 l_Position;
layout (location = 1) in vec2 l_TexCoord;

out vec2 texCoord;

void main()
{
   gl_Position = vec4(l_Position.x, l_Position.y, l_Position.z, 1.0);
   texCoord = l_TexCoord;
}