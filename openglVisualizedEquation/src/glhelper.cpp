#include "glhelper.hpp"

#include <array>
#include <stdexcept>
#include <algorithm>

#include "parameters.h"

std::array<INDEX_TYPE, AMOUNT_OF_TRIANGLE_INDICES> CreateUpperTriangleIndices(const unsigned int grid_width, const unsigned int grid_height)
{
    std::array<INDEX_TYPE, AMOUNT_OF_TRIANGLE_INDICES> upper_triangle_indices;
    auto upper_triangle_index_iterator = upper_triangle_indices.begin();

    for (int j = 0; j < grid_height-1; ++j)
    {
        for(int i = 0; i < grid_width-1; ++i)
        {
            *upper_triangle_index_iterator = i + j * grid_width;
            upper_triangle_index_iterator++;
            *upper_triangle_index_iterator = i + j * grid_width + 1;
            upper_triangle_index_iterator++;
            *upper_triangle_index_iterator = i + (j+1) * grid_width;
            upper_triangle_index_iterator++;
        }
    }

    return upper_triangle_indices;
}

std::array<INDEX_TYPE, AMOUNT_OF_TRIANGLE_INDICES> CreateLowerTriangleIndices(const unsigned int grid_width, const unsigned int grid_height)
{
    std::array<INDEX_TYPE, AMOUNT_OF_TRIANGLE_INDICES> upper_triangle_indices;
    auto upper_triangle_index_iterator = upper_triangle_indices.begin();

    for (int j = 0; j < grid_height-1; ++j)
    {
        for(int i = 0; i < grid_width-1; ++i)
        {
            *upper_triangle_index_iterator = i + j * grid_width + 1;
            upper_triangle_index_iterator++;
            *upper_triangle_index_iterator = i + (j+1) * grid_width + 1;
            upper_triangle_index_iterator++;
            *upper_triangle_index_iterator = i + (j+1) * grid_width;
            upper_triangle_index_iterator++;
        }
    }

    return upper_triangle_indices;
}

std::array<PRECISION_TYPE, AMOUNT_OF_GRID_POINTS * SPATIAL_DIMENSIONS> CreatePositionArray(const unsigned int grid_width, const unsigned int grid_height, const float x_step_size, const float y_step_size)
{
	std::array<PRECISION_TYPE, AMOUNT_OF_GRID_POINTS * SPATIAL_DIMENSIONS> positions;  
	auto position_iterator = positions.begin();

	for (int j = 0; j < grid_height; ++j)
	{
		for(int i = 0; i < grid_width; ++i)
		{
			*position_iterator = -1.0f + i * x_step_size;
			position_iterator++;
			*position_iterator = 1.0f - j * y_step_size;
			position_iterator++;
			*position_iterator = 0.0f;
			position_iterator++;
		}
	}

    return positions;
}

void ChangeVertexValuesAround(const double& x, const double& y, std::array<bool, AMOUNT_OF_GRID_POINTS>& bool_array, const std::array<PRECISION_TYPE, AMOUNT_OF_GRID_POINTS * SPATIAL_DIMENSIONS>& vertex_array)
{
	auto x_iter = vertex_array.cbegin();
	auto y_iter = vertex_array.cbegin() + 1;
	for (auto& bool_val : bool_array)
	{
		auto dist_x = x-*x_iter;
		auto dist_y = y-*y_iter;

		bool_val = (dist_x*dist_x + dist_y*dist_y) < 0.025;

		x_iter += 3;
		y_iter += 3;
	}
}

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

	SmartGLFWWindow window = SmartGLFWWindow(glfwCreateWindow(width, height, "OpenGL", NULL, NULL));

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