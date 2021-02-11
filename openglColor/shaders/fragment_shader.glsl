#version 330 core
out vec4 fragment_color;
in vec3 my_color;
in float TexCoord;

uniform sampler1D color_palette;
  
void main()
{
    fragment_color = texture(color_palette,TexCoord);
}   
