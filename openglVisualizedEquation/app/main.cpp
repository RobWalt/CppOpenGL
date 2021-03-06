// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <filesystem>
#include <optional>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "utilities.hpp"
#include "glhelper.hpp"
#include "physics.hpp"
#include "color_palette.h"
#include "project_variables.h"
#include "parameters.h"

#include <array>

int main() 
{
	// Test area
	std::cout << CPP_STANDARD << std::endl;
	Grid<3> grid{Position{1.0f, 1.0f},
				 Position{1.0f, 0.0f},
				 Position{0.0f, 0.0f}};
	Heatmap test{grid, {0,1,2}};
	//auto test = CreateTriangleIndices<2,3>();
	// End Test area

	auto window = CreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

	DifferentialEquation DEQ(DIFF_EQ_C, DIFF_EQ_DX, DIFF_EQ_DT);

	// GPU data part II

	auto all_triangle_indices = CreateTriangleIndices<GRID_WIDTH, GRID_HEIGHT>();

	auto positions = CreatePositionArray(GRID_WIDTH, GRID_HEIGHT, STEPSIZE_X, STEPSIZE_Y);
	std::array<bool, AMOUNT_OF_GRID_POINTS> is_clicked;

	auto colors = DEQ.get_current_solution();

	// load color palette from file
	const std::string color_palette_path = RESOURCE_DIR "/fire_palette.txt";
	ColorPalette color_palette(color_palette_path);

	unsigned int VBO, VAO, EBO, texture;

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
	glVertexAttribPointer(0, SPATIAL_DIMENSIONS, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, COLOR_CHANNELS, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(positions)));
	glEnableVertexAttribArray(1);

	// fill uniform in fragment shader with data
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_1D, texture);

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, color_palette.data.size(), 0, GL_RGB, GL_UNSIGNED_BYTE, color_palette.c_array());
	glGenerateMipmap(GL_TEXTURE_1D);

	// VAO initialization

	std::string vertex_shader_path = SHADER_DIR "/vertex_shader.glsl";
	std::string fragment_shader_path = SHADER_DIR "/fragment_shader.glsl";
	ShaderSourceCode our_shader(vertex_shader_path, fragment_shader_path);

	// bind sampler1D color_palette to our texture
	our_shader.use();
	our_shader.SetUniform(0, "color_palette");

	auto accumulated_time = 0.0f;
	auto last_time = 0.0f;
	auto mouseClickEventShouldTrigger = true;

	while(!glfwWindowShouldClose(window.get()))
	{
		// Process inputs
		processInput(window.get());
		auto mouse_clicked = processMouseInput(window.get(), mouseClickEventShouldTrigger);
		if (mouse_clicked)
		{
			std::array<double, 2> vert_mouse_data = PixelCoordsToVertexCoords((*mouse_clicked)[0], (*mouse_clicked)[1], WINDOW_WIDTH, WINDOW_HEIGHT);
			ChangeVertexValuesAround(vert_mouse_data[0], vert_mouse_data[1], is_clicked, positions);
			DEQ.add_heat(is_clicked);
		}
		//render
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear( GL_COLOR_BUFFER_BIT );

		// render triangle
		our_shader.use();

		glBindVertexArray(VAO);
		//bind texture to corresponding texture unit
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_1D, texture);

		auto current_time = glfwGetTime();

		auto time_passed_this_iteration = current_time - last_time;
		accumulated_time += time_passed_this_iteration;
		last_time = current_time;
		if (accumulated_time >= DIFF_EQ_DT)
		{
			DEQ.solver_step();
			colors = DEQ.get_current_solution();
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors.data());
			accumulated_time = 0.0f;
		}

		glDrawElements(GL_TRIANGLES, AMOUNT_OF_TRIANGLE_INDICES_TOTAL, GL_UNSIGNED_INT, 0);

		// Poll events
		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}
