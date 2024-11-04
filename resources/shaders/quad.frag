// #version 400 core
#version 460 core

in vec2 Tex;

out vec4 FragColor;

uniform sampler2D texture0;

void main()
{
    FragColor = vec4(vec3(texture(texture0, Tex)), 1);
    // gl_FragColor = vec4(vec3(texture2D(texture0, Tex)), 1);
}