#include <array>

template <typename T, int amount_of_vertices, int spacial_dimensions, int color_channels>
auto CreateInterlacedArray(std::array<T, amount_of_vertices * spacial_dimensions> position_array, std::array<T, amount_of_vertices * color_channels> color_array)  
{
	std::array<T, position_array.size() + color_array.size()> interlaced_array;

	auto position_iterator = position_array.begin();
	auto color_iterator = color_array.begin();
	auto interlaced_iterator = interlaced_array.begin();

	for (int i = 0; i < amount_of_vertices; ++i)
	{
		for (int j=0; j < spacial_dimensions; ++j)
		{
			*interlaced_iterator = *position_iterator;
			position_iterator++;
			interlaced_iterator++;
		}
		for (int j=0; j < color_channels; ++j)
		{
			*interlaced_iterator = *color_iterator;
			color_iterator++;
			interlaced_iterator++;
		}
	}

	return interlaced_array;
}

template <typename index_type, int amount_of_triangles>
auto CreateUpperTriangleIndices(const unsigned int grid_width, const unsigned int grid_height)
{
    std::array<index_type, amount_of_triangles * 3> upper_triangle_indices;
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

template <typename position_type, int amount_of_vertices, int spacial_dimensions>
auto CreatePositionArray(const unsigned int grid_width, const unsigned int grid_height, const float x_step_size, const float y_step_size)
{
	std::array<position_type, amount_of_vertices * spacial_dimensions> positions;  
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