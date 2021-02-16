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
#include "glhelper.hpp"
#include "physics.hpp"
#include "project_variables.h"

#include <array>

// manual set parameters
constexpr unsigned int  my_color_channels = 1;
constexpr unsigned int  my_spacial_dimensions = 3;
constexpr unsigned int  my_grid_width = 101;
constexpr unsigned int  my_grid_height = 101;
constexpr float 		my_x_step_size = 0.02f;
constexpr float 		my_y_step_size = 0.02f;

// deduced parameters
constexpr unsigned int my_amount_of_vertices = my_grid_width * my_grid_height;
constexpr unsigned int my_amount_of_upper_triangles = my_amount_of_vertices - my_grid_height - my_grid_width + 1;
constexpr unsigned int my_amount_of_lower_triangles = my_amount_of_upper_triangles;
constexpr unsigned int my_amount_of_triangles = my_amount_of_upper_triangles + my_amount_of_lower_triangles;


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

	constexpr float dx = 1.0f;
	constexpr float c = 1.0f;
	constexpr float dt = 0.1 * (dx * dx) / (c * c);
	DifferentialEquation DEQ(c, dx, dt);

	// GPU data part II
	auto upper_triangle_indices = CreateUpperTriangleIndices<unsigned int, my_amount_of_upper_triangles>(my_grid_width, my_grid_height);
	auto lower_triangle_indices = CreateLowerTriangleIndices<unsigned int, my_amount_of_upper_triangles>(my_grid_width, my_grid_height);

	auto all_triangle_indices = ConcatenateArrays(upper_triangle_indices, lower_triangle_indices);

	auto positions = CreatePositionArray<float, my_amount_of_vertices, my_spacial_dimensions>(my_grid_width, my_grid_height, my_x_step_size, my_y_step_size);

	auto colors = DEQ.get_current_solution();

	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions.data());
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors.data());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(all_triangle_indices), all_triangle_indices.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, my_spacial_dimensions, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, my_color_channels, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(positions)));
	glEnableVertexAttribArray(1);

	std::string vertex_shader_path = SHADER_DIR "/vertex_shader.glsl";
	std::string fragment_shader_path = SHADER_DIR "/fragment_shader.glsl";
	ShaderSourceCode our_shader(vertex_shader_path, fragment_shader_path);

	auto accumulated_time = 0.0f;
	auto last_time = 0.0f;

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

		auto current_time = glfwGetTime();

		auto time_passed_this_iteration = current_time - last_time;
		accumulated_time += time_passed_this_iteration;
		last_time = current_time;
		if (accumulated_time >= dt)
		{
			DEQ.solver_step();
			colors = DEQ.get_current_solution();
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors.data());
			accumulated_time = 0.0f;
		}

		glDrawElements(GL_TRIANGLES, 3*my_amount_of_triangles, GL_UNSIGNED_INT, 0);

		// Poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}
