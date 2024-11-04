// #version 400 core
#version 460 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTex;

// attribute vec2 aPos;
// attribute vec2 aTex;

out vec2 Tex;

uniform float x;
uniform mat4 u_model;

mat4 model = mat4(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0.5, -0.5, 0, 1
);

mat4 model1 = mat4(
    vec4(1, 0, 0, 0),
    vec4(0, 1, 0, 0),
    vec4(0, 0, 1, 0),
    vec4(0.5, -0.5, 0, 1)
);

// out vec2 Tex;

void main()
{
    gl_Position = u_model * vec4(aPos, 0, 1);
    // gl_Position = vec4(aPos, 0, 1);
    Tex = aTex;
}