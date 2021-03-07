#pragma once

#include <array>
#include <vector>
#include <stdexcept>
#include <boost/range/combine.hpp>
#include <glad/glad.h>
#include "parameters.h"

// Header + Implementation
std::array<INDEX_TYPE, AMOUNT_OF_TRIANGLE_INDICES> CreateUpperTriangleIndices(const unsigned int grid_width, const unsigned int grid_height);

std::array<INDEX_TYPE, AMOUNT_OF_TRIANGLE_INDICES> CreateLowerTriangleIndices(const unsigned int grid_width, const unsigned int grid_height);

std::array<PRECISION_TYPE, AMOUNT_OF_GRID_POINTS * SPATIAL_DIMENSIONS> CreatePositionArray(const unsigned int grid_width, const unsigned int grid_height, const float x_step_size, const float y_step_size);

void ChangeVertexValuesAround(const double& x, const double& y, std::array<bool, AMOUNT_OF_GRID_POINTS>& bool_array, const std::array<PRECISION_TYPE, AMOUNT_OF_GRID_POINTS * SPATIAL_DIMENSIONS>& vertex_array);

// Header Only
template <typename Type, std::size_t size1, std::size_t size2>
auto InterleaveArrays(const std::size_t & number_of_vertices, const std::array<Type, size1> & array1, const std::array<Type, size2> & array2);

template<typename T, std::size_t N, std::size_t M>
auto ConcatenateArrays(const std::array<T, N>& array1, const std::array<T, M>& array2);

// Heatmap
using PrecisionType = GLfloat;
template<typename std::size_t N>
using DomainType = std::array<PrecisionType,N>;

template<std::size_t N>
class Heatmap{
				DomainType<N> data_;
				
				public:
				Heatmap(const DomainType<N> & data);

};


#include "glhelper_impl.hpp"
