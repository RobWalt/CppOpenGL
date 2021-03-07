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

std::array<double, 2> PixelCoordsToVertexCoords(double x_pix, double y_pix, unsigned int window_width, unsigned int window_height)
{
    auto x_vert = (x_pix / window_width) * 2.0 - 1;
    auto y_vert = ((window_height - y_pix) / window_height) * 2.0 - 1;
    return std::array<double, 2>{x_vert, y_vert};
}

struct DestroyGLFWWindow{

    void operator()(GLFWwindow* ptr){
         glfwDestroyWindow(ptr);
    }

};

using SmartGLFWWindow = std::unique_ptr<GLFWwindow,DestroyGLFWWindow>;

SmartGLFWWindow CreateWindow(const unsigned int width, const unsigned int height){
	// Start of window class;
	
	//glfwInit();
	// Initialise GLFW
	if( !glfwInit() )
	{
		throw std::runtime_error("Failed to initialize GLFW\n");
 	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	SmartGLFWWindow window = SmartGLFWWindow(glfwCreateWindow(width, heigth, "OpenGL", NULL, NULL));

	if( window == NULL ){
				glfwTerminate();
				throw std::runtime_error("Failed to open GLFW window.");
	}

	glfwMakeContextCurrent(window.get());

	if (! gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		throw std::runtime_error("Failed to load glad.");
	}
	// End of window class
	
	return window;
}

int main()
{
	auto window = CreateWindow(width,heigth);

	constexpr float dx = 1.0f;
	constexpr float c = 5.0f;
	constexpr float dt = 0.20 * (dx * dx) / (c * c);
	DifferentialEquation DEQ(c, dx, dt);

	// GPU data part II
	auto upper_triangle_indices = CreateUpperTriangleIndices<unsigned int, my_amount_of_upper_triangles>(my_grid_width, my_grid_height);
	auto lower_triangle_indices = CreateLowerTriangleIndices<unsigned int, my_amount_of_upper_triangles>(my_grid_width, my_grid_height);

	auto all_triangle_indices = ConcatenateArrays(upper_triangle_indices, lower_triangle_indices);

	auto positions = CreatePositionArray<float, my_amount_of_vertices, my_spacial_dimensions>(my_grid_width, my_grid_height, my_x_step_size, my_y_step_size);
	std::array<bool, my_amount_of_vertices> is_clicked;

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
	glVertexAttribPointer(0, my_spacial_dimensions, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, my_color_channels, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(positions)));
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
			std::array<double, 2> vert_mouse_data = PixelCoordsToVertexCoords((*mouse_clicked)[0], (*mouse_clicked)[1], width, heigth);
			ChangeVertexValuesAround<float, my_amount_of_vertices, my_spacial_dimensions>(vert_mouse_data[0], vert_mouse_data[1], is_clicked, positions);
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
		if (accumulated_time >= dt)
		{
			DEQ.solver_step();
			colors = DEQ.get_current_solution();
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors.data());
			accumulated_time = 0.0f;
		}

		glDrawElements(GL_TRIANGLES, 3*my_amount_of_triangles, GL_UNSIGNED_INT, 0);

		// Poll events
		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}
