#version 460 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 texPos;

out vec2 texCoord;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 projection;

void main()
{
    gl_Position = projection * (translation + rotation) * scale * vec4(pos, 0.0, 1.0);
    texCoord = texPos;
}

