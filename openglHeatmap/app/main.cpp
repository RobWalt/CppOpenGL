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

#include <array>

// manual set parameters
constexpr unsigned int  my_color_channels = 3;
constexpr unsigned int  my_spacial_dimensions = 3;
constexpr unsigned int  my_grid_width = 20;
constexpr unsigned int  my_grid_height = 20;
constexpr float 		my_x_step_size = 0.1f;
constexpr float 		my_y_step_size = 0.1f;

// deduced parameters
constexpr unsigned int my_amount_of_vertices = my_grid_width * my_grid_height;
constexpr unsigned int my_amount_of_upper_triangles = my_amount_of_vertices - my_grid_height - my_grid_width + 1;
constexpr unsigned int my_amount_of_lower_triangles = my_amount_of_upper_triangles;
constexpr unsigned int my_vertex_length = my_spacial_dimensions + my_color_channels;

template <typename T, int amount_of_vertices, int spacial_dimensions, int color_channels>
auto CreateInterlacedArray(std::array<T, amount_of_vertices * spacial_dimensions> position_array, std::array<T, amount_of_vertices * color_channels> color_array)  
{
	std::array<T, position_array.size() + color_array.size()> interlaced_array;

	auto position_iterator = position_array.begin();
	auto color_iterator = color_array.begin();
	auto interlaced_iterator = interlaced_array.begin();

	for (int i = 0; i < amount_of_vertices; ++i)
	{
		for (int j=0; j < spacial_dimensions; ++j)
		{
			*interlaced_iterator = *position_iterator;
			position_iterator++;
			interlaced_iterator++;
		}
		for (int j=0; j < color_channels; ++j)
		{
			*interlaced_iterator = *color_iterator;
			color_iterator++;
			interlaced_iterator++;
		}
	}

	return interlaced_array;
}

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
	     0.0f,  0.5f, 0.0f,
	};  

	// GPU data part II

	std::array<unsigned int, my_amount_of_upper_triangles * 3> upper_triangle_indices;
	auto upper_triangle_index_iterator = upper_triangle_indices.begin();

	for (int j = 0; j < my_grid_height-1; ++j)
	{
		for(int i = 0; i < my_grid_width-1; ++i)
		{
			*upper_triangle_index_iterator = i + j * my_grid_width;
			upper_triangle_index_iterator++;
			*upper_triangle_index_iterator = i + j * my_grid_width + 1;
			upper_triangle_index_iterator++;
			*upper_triangle_index_iterator = i + (j+1) * my_grid_width;
			upper_triangle_index_iterator++;
		}
	}

	std::array<float, my_amount_of_vertices * my_spacial_dimensions> positions;  
	auto position_iterator = positions.begin();

	for (int j = 0; j < my_grid_height; ++j)
	{
		for(int i = 0; i < my_grid_width; ++i)
		{
			*position_iterator = -1.0f + i * my_x_step_size;
			position_iterator++;
			*position_iterator = 1.0f - j * my_y_step_size;
			position_iterator++;
			*position_iterator = 0.0f;
			position_iterator++;
		}
	}

	std::array<float, my_amount_of_vertices * my_color_channels> colors = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};

	auto interlaced_triangle_vertices = CreateInterlacedArray<float, my_amount_of_vertices, my_spacial_dimensions, my_color_channels>(positions, colors);

	//for (auto& value : upper_triangle_indices)
	//{
	//	std::cout << value << " ";
	//}
	//std::cout << "\n";
	//for (auto& value : positions)
	//{
	//	std::cout << value << " ";
	//}

	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(interlaced_triangle_vertices), interlaced_triangle_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(upper_triangle_indices), upper_triangle_indices.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, my_spacial_dimensions, GL_FLOAT, GL_FALSE, my_vertex_length * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, my_color_channels, GL_FLOAT, GL_FALSE, my_vertex_length * sizeof(float), (void*)(my_spacial_dimensions * sizeof(float)));
	glEnableVertexAttribArray(1);

	std::string vertex_shader_path = SHADER_DIR "/vertex_shader.glsl";
	std::string fragment_shader_path = SHADER_DIR "/fragment_shader.glsl";
	ShaderSourceCode our_shader(vertex_shader_path, fragment_shader_path);

	while(!glfwWindowShouldClose(window))
	{
		// Process inputs
		processInput(window);

		//render
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear( GL_COLOR_BUFFER_BIT );

		// render triangle
		our_shader.use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3*my_amount_of_upper_triangles, GL_UNSIGNED_INT, 0);

		// Poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}
