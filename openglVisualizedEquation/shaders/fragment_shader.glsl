#version 330 core
out vec4 frag_color;
in float my_color;
  
void main()
{
    frag_color = vec4(my_color, my_color, my_color, 0.0f);
}   
