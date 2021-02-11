#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in float aTexCoord;

out vec3 my_color;
out float TexCoord;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);
	my_color = vec3(0.0f,0.0f,0.0f);
	TexCoord = aTexCoord;
}
