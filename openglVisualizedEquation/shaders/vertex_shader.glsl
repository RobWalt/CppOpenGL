#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in float color;

out float my_color;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    my_color = color;
}
