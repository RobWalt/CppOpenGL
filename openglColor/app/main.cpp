#include <iostream>
#include <array>
#include <list>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <fstream>


#include <glad/glad.h> 
 #include <GLFW/glfw3.h>

#include "shader.hpp"
#include "color_palette.h"
#include "utilities.h"
#include "variables.h"

constexpr int width = 600;
constexpr int height = 600;

constexpr unsigned int spatial_dimensions = 2;
constexpr unsigned int texture_coord_dimensions = 1;
constexpr unsigned int number_of_triangles = 2;
constexpr unsigned int number_of_vertices = 4;

constexpr unsigned int vertex_size = spatial_dimensions + texture_coord_dimensions;

int main()
{
	//Initialise GLFW
	if (!glfwInit())
	{
		throw std::runtime_error("Faild to initialize GLFW.");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Hint for MAC 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window =glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	if (! gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to load glad" << std::endl;
		return EXIT_FAILURE;
	}

	// vertices
	std::array vertex_positions{
		 0.5f,  0.5f, // upper right
		-0.5f,  0.5f, // upper left
		 0.5f, -0.5f, // lower right
		-0.5f, -0.5f, // lower left 
	};

	// indices for two triangles
	std::array vertex_indices{
		0, 1, 3,
		0, 2, 3,
	};
	
	std::array vertex_texture_coFordinates{
		 1.0f,
		 0.0f,
		 1.0f,
		 0.0f,
	};

	std::unordered_map<std::string,GLuint> VAOs;
	std::unordered_map<std::string,GLuint> VBOs;
	std::unordered_map<std::string,GLuint> EBOs;
	std::unordered_map<std::string,GLuint> textures;

	// make data loading instructions for later use
	glGenVertexArrays(1, &VAOs["square"]);
	glGenBuffers(1, &VBOs["square"]);
	glGenBuffers(1, &EBOs["square"]);

	glBindVertexArray(VAOs["square"]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs["square"]);
	std::array vertices = InterleaveArrays(number_of_vertices,vertex_positions, vertex_texture_coordinates); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs["square"]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices.data(), GL_STATIC_DRAW); 

	// load position data to GPU
	glVertexAttribPointer(0, spatial_dimensions,GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// load texture coordinate data to GPU
	glVertexAttribPointer(1, texture_coord_dimensions,GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), (void*) (spatial_dimensions * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// load shader source code, compile and link it.
	const std::string vertex_shader_path = SHADER_DIR "/vertex_shader.glsl";
	const std::string fragment_shader_path = SHADER_DIR "/fragment_shader.glsl";
	ShaderSourceCode shader_square(vertex_shader_path, fragment_shader_path);

	// load color palette from file
	const std::string color_palette_path = RESOURCE_DIR "/fire_palette.txt";
	ColorPalette color_palette(color_palette_path);
	
	// fill uniform in fragment shader with data
	glGenTextures(1, &textures["square"]);
	glBindTexture(GL_TEXTURE_1D, textures["square"]);

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	unsigned char * color_palette_c_array =  
										(unsigned char*) malloc( 
										sizeof(unsigned char)*3*color_palette.data.size() );
	color_palette.ToCArray(color_palette_c_array);

	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, color_palette.data.size(), 0, GL_RGB, GL_UNSIGNED_BYTE, color_palette_c_array);
	glGenerateMipmap(GL_TEXTURE_1D);

	// bind sampler1D color_palette to our texture
	shader_square.use();
	shader_square.SetUniform(0, "color_palette");

	while(!glfwWindowShouldClose(window))
	{
		//input

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//square
		shader_square.use();

		//bind texture to corresponding texture unit
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_1D, textures["square"]);

		glBindVertexArray(VAOs["square"]);
		glDrawElements(GL_TRIANGLES, 3*number_of_triangles, GL_UNSIGNED_INT,0);

		glfwSwapBuffers(window);
		glfwPollEvents();    
	}				

	glfwTerminate();
	return EXIT_SUCCESS;
}
