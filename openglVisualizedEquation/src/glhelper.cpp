#include "glhelper.hpp"

#include <array>
#include <stdexcept>
#include <algorithm>

#include "parameters.h"


void CheckVertexData(const unsigned int & number_of_vertices, const std::span<PRECISION_TYPE> & data) {
				if (data.size() % number_of_vertices != 0) {
								throw std::runtime_error("Size of data needs to be multiple of number_of_vertices.");
				}
}

std::array<INDEX_TYPE,3> LoadVertexData(
				unsigned int number_of_vertices,
				std::span<INDEX_TYPE> indices,
				std::span<std::span<PRECISION_TYPE>> data_list,
				std::span<INDEX_TYPE> location_list
				){

				INDEX_TYPE VAO, VBO, EBO;

				for(const auto & data : data_list) {
								CheckVertexData(number_of_vertices, data);
				}

				if (data_list.size() != location_list.size()) {
								throw std::runtime_error("Number of items in data_list does not match number of items in data_names.");
				}

				glGenVertexArrays(1, &VAO);
				glGenBuffers(1, &VBO);
				glGenBuffers(1, &EBO);

				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);

				std::size_t total_data_size = 0;
				for (const auto & data : data_list) {
								total_data_size += sizeof(PRECISION_TYPE)* data.size();
				}

				std::size_t size_of_loaded_data = 0;
				glBufferData(GL_ARRAY_BUFFER, total_data_size, nullptr, GL_STATIC_DRAW);
				for (auto [data,location] : boost::combine(data_list,location_list))
				{
								glBufferSubData(GL_ARRAY_BUFFER,
																size_of_loaded_data,
																sizeof(PRECISION_TYPE)* data.size(),
																data.data());

								std::size_t dimension = data.size() / number_of_vertices;

								glVertexAttribPointer(location,
															 	dimension,
																GL_FLOAT,
															 	GL_FALSE,
															 	0,
															 	(void*) size_of_loaded_data);
								glEnableVertexAttribArray(location);

								size_of_loaded_data += sizeof(PRECISION_TYPE)* data.size();
				}

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER,
											 	sizeof(INDEX_TYPE)*indices.size(),
											 	indices.data(),
											 	GL_STATIC_DRAW); 
				return {VAO,VBO,EBO};
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

std::vector<GLfloat> Expand(const std::span<Position> & v)
{
        unsigned int dimension = v[0].Position::dimension;

        std::vector<GLfloat> result{};
        result.reserve(v.size()*dimension);

        for (const auto & position : v)
        {
                std::copy(position.coordinates.cbegin(), position.coordinates.cend(), std::back_inserter(result));
        }
        return result;
}
