#version 330 core
out vec4 frag_color;
in float my_color;
  
uniform sampler1D color_palette;

void main()
{
    frag_color = texture(color_palette,my_color);
}   
