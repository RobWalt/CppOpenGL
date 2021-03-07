#pragma once

#include <array>
#include <vector>
#include <stdexcept>
#include <boost/range/combine.hpp>
#include <glad/glad.h>

template <typename Type, std::size_t size1, std::size_t size2>
auto InterleaveArrays(const std::size_t & number_of_vertices, const std::array<Type, size1> & array1, const std::array<Type, size2> & array2);

template <typename index_type, int amount_of_triangles>
auto CreateUpperTriangleIndices(const unsigned int grid_width, const unsigned int grid_height);

template <typename index_type, int amount_of_triangles>
auto CreateLowerTriangleIndices(const unsigned int grid_width, const unsigned int grid_height);

template <typename position_type, int amount_of_vertices, int spacial_dimensions>
auto CreatePositionArray(const unsigned int grid_width, const unsigned int grid_height, const float x_step_size, const float y_step_size);

template<typename T, std::size_t N, std::size_t M>
auto ConcatenateArrays(const std::array<T, N>& array1, const std::array<T, M>& array2);

template<typename position_type, std::size_t amount_of_vertices, std::size_t spacial_dimensions>
void ChangeVertexValuesAround(const double& x, const double& y, std::array<bool, amount_of_vertices>& bool_array, const std::array<position_type, spacial_dimensions * amount_of_vertices>& vertex_array);

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
