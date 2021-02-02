#pragma once

#include <array>

template <typename T, int amount_of_vertices, int spacial_dimensions, int color_channels>
auto CreateInterlacedArray(std::array<T, amount_of_vertices * spacial_dimensions> position_array, std::array<T, amount_of_vertices * color_channels> color_array);  

template <typename index_type, int amount_of_triangles>
auto CreateUpperTriangleIndices(const unsigned int grid_width, const unsigned int grid_height);

template <typename position_type, int amount_of_vertices, int spacial_dimensions>
auto CreatePositionArray(const unsigned int grid_width, const unsigned int grid_height, const float x_step_size, const float y_step_size);

#include "glhelper_impl.hpp"