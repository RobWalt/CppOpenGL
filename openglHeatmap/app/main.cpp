// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <filesystem>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "utilities.hpp"
#include "project_variables.h"

// Settings.
const unsigned int width = 800;
const unsigned int heigth = 600;

int main()
{
	//glfwInit();
	// Initialise GLFW
        if( !glfwInit() )
        {
                fprintf( stderr, "Failed to initialize GLFW\n" );
                getchar();
                return -1;
        }


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	GLFWwindow* window =glfwCreateWindow(width, heigth, "OpenGL", NULL, NULL);

	if( window == NULL ){
                fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
                getchar();
                glfwTerminate();
                return -1;
        }


	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
                fprintf(stderr, "Failed to initialize GLEW\n");
                getchar();
                glfwTerminate();
                return -1;
        }

	// GPU data
	float vertices[] = {
	    -0.5f, -0.5f, 0.0f,
	     0.5f, -0.5f, 0.0f,
	     0.0f,  0.5f, 0.0f
	};  

	// GPU data part II
	float upside_down_vertices[] = {
	    -0.5f, 0.5f, 0.0f,
	     0.5f, 0.5f, 0.0f,
	     0.0f, -0.5f, 0.0f
	};  


	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int VBO_upside_down, VAO_upside_down;
	glGenVertexArrays(1, &VAO_upside_down);
	glGenBuffers(1, &VBO_upside_down);
	    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_upside_down);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_upside_down);
	glBufferData(GL_ARRAY_BUFFER, sizeof(upside_down_vertices), upside_down_vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	std::string vertex_shader_path = SHADER_DIR "/vertex_shader.glsl";
	std::string fragment_shader_path = SHADER_DIR "/fragment_shader.glsl";
	ShaderSourceCode our_shader(vertex_shader_path, fragment_shader_path);

	unsigned int vertexColorLocation = glGetUniformLocation(our_shader.program_id_, "off_set");

	while(!glfwWindowShouldClose(window))
	{
		// Process inputs
		processInput(window);

		//render
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear( GL_COLOR_BUFFER_BIT );

		// render triangle
		our_shader.use();
		float time_value = glfwGetTime();
		our_shader.SetUniform(time_value, "time");

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// Poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}
