#ifndef GLHELPER
#define GLHELPER

#include <array>
#include <vector>
#include <stdexcept>
#include <boost/range/combine.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <span>
#include "parameters.h"

// Header + Implementation
std::array<PRECISION_TYPE, AMOUNT_OF_GRID_POINTS * SPATIAL_DIMENSIONS> CreatePositionArray(const unsigned int grid_width, const unsigned int grid_height, const float x_step_size, const float y_step_size);

void ChangeVertexValuesAround(const double& x, const double& y, std::array<bool, AMOUNT_OF_GRID_POINTS>& bool_array, const std::array<PRECISION_TYPE, AMOUNT_OF_GRID_POINTS * SPATIAL_DIMENSIONS>& vertex_array);

struct DestroyGLFWWindow{

    void operator()(GLFWwindow* ptr){
         glfwDestroyWindow(ptr);
    }

};

using SmartGLFWWindow = std::unique_ptr<GLFWwindow,DestroyGLFWWindow>;
SmartGLFWWindow CreateWindow(const unsigned int width, const unsigned int height);

// Header Only

template <std::size_t grid_width, std::size_t grid_height>
std::array<INDEX_TYPE, (grid_width - 1) * (grid_height - 1) * 3> CreateUpperTriangleIndices();

template <std::size_t grid_width, std::size_t grid_height>
std::array<INDEX_TYPE, (grid_width - 1) * (grid_height - 1) * 3> CreateLowerTriangleIndices();

template <typename Type, std::size_t size1, std::size_t size2>
auto InterleaveArrays(const std::size_t & number_of_vertices, const std::array<Type, size1> & array1, const std::array<Type, size2> & array2);

template<typename T, std::size_t N, std::size_t M>
auto ConcatenateArrays(const std::array<T, N>& array1, const std::array<T, M>& array2);

template<std::size_t grid_width, std::size_t grid_height>
std::array<INDEX_TYPE,(grid_width-1)*(grid_height-1)*2*3>CreateTriangleIndices();

// Heatmap
template<typename std::size_t N>
using DomainType = std::array<PRECISION_TYPE,N>;

class Position {
	public:
		std::array<PRECISION_TYPE,2> coordinates;
		static const unsigned int dimension = 2;
};

template<std::size_t N>
using Grid = std::array<Position,N>;

template<std::size_t N>
using Indice_array = std::array<INDEX_TYPE,N>;

template<std::size_t N>
class Heatmap{
		DomainType<N> data_;
		
	public:
		Heatmap(const Grid<N> & grid, const Indice_array<N>& indices);

};

void CheckVertexData(const unsigned int & number_of_vertices, const std::vector<PRECISION_TYPE> & data);

std::vector<GLfloat> Expand(const std::span<Position> & v);

std::array<INDEX_TYPE,3> LoadVertexData(
				unsigned int number_of_vertices,
				std::span<INDEX_TYPE> indices,
				std::initializer_list<std::vector<PRECISION_TYPE>> data_list,
				std::initializer_list<INDEX_TYPE> location_list
				);

#include "glhelper_impl.hpp"

#endif
