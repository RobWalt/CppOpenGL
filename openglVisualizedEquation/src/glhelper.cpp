#include "glhelper.hpp"

void CheckVertexData(const unsigned int & number_of_vertices, const std::vector<GLfloat> & data) {
				if (data.size() % number_of_vertices != 0) {
								throw std::runtime_error("Size of data needs to be multiple of number_of_vertices.");
				}
}

std::array<GLuint,3> LoadVertexData(
				unsigned int number_of_vertices,
				std::vector<GLuint> indices,
				std::initializer_list<std::vector<GLfloat>> data_list,
				std::initializer_list<GLuint> location_list
				){

				GLuint VAO, VBO, EBO;

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
								total_data_size += sizeof(GLfloat)* data.size();
				}

				std::size_t size_of_loaded_data = 0;
				glBufferData(GL_ARRAY_BUFFER, total_data_size, nullptr, GL_STATIC_DRAW);
				for (auto [data,location] : boost::combine(data_list,location_list))
				{
								glBufferSubData(GL_ARRAY_BUFFER,
																size_of_loaded_data,
																sizeof(GLfloat)* data.size(),
																data.data());

								std::size_t dimension = data.size() / number_of_vertices;

								glVertexAttribPointer(location,
															 	dimension,
																GL_FLOAT,
															 	GL_FALSE,
															 	0,
															 	(void*) size_of_loaded_data);
								glEnableVertexAttribArray(location);

								size_of_loaded_data += sizeof(GLfloat)* data.size();
				}

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER,
											 	sizeof(GLuint)*indices.size(),
											 	indices.data(),
											 	GL_STATIC_DRAW); 
				return {VAO,VBO,EBO};
}
