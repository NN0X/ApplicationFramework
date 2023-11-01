#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texPos;

out vec2 texCoord;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 camera;

void main()
{
    gl_Position = camera * (translation + rotation) * scale * vec4(pos, 1.0);
    texCoord = texPos;
}

