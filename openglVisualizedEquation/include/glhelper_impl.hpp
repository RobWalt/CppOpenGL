#include <array>
#include <stdexcept>
#include <algorithm>

template <typename Type, std::size_t size1, std::size_t size2>
auto InterleaveArrays(const std::size_t & number_of_vertices, const std::array<Type, size1> & array1, const std::array<Type, size2> & array2)
{
    std::array<Type, size1 + size2> result;
		if(size1 % number_of_vertices != 0)
		{
						throw std::runtime_error("array1.size() needs to be divisible by number_of_vertices");
		}
		if(size2 % number_of_vertices != 0)
		{
						throw std::runtime_error("array2.size() needs to be divisible by number_of_vertices");
		}

		std::size_t number_of_dimensions_1 = size1 / number_of_vertices;
		std::size_t number_of_dimensions_2 = size2 / number_of_vertices;

		auto it_1 = array1.begin();
		auto it_2 = array2.begin();
		auto it_result = result.begin();
		for (std::size_t i = 0; i < number_of_vertices; i++)
		{
						for (std::size_t j = 0; j < number_of_dimensions_1; j++)
						{
										*it_result = *it_1;
										it_result++;
										it_1++;
						}
						for (std::size_t j = number_of_dimensions_1; j < number_of_dimensions_1 + number_of_dimensions_2; j++)
						{
										*it_result = *it_2;
										it_result++;
										it_2++;
						}
		}
    return result;
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

template <typename index_type, int amount_of_triangles>
auto CreateLowerTriangleIndices(const unsigned int grid_width, const unsigned int grid_height)
{
    std::array<index_type, amount_of_triangles * 3> upper_triangle_indices;
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

template<typename T, std::size_t N, std::size_t M>
auto ConcatenateArrays(const std::array<T, N>& array1, const std::array<T, M>& array2)
{
    std::array<T, N+M> result;
    std::copy (array1.cbegin(), array1.cend(), result.begin());
    std::copy (array2.cbegin(), array2.cend(), result.begin() + N);
    return result;
}

template<typename position_type, std::size_t amount_of_vertices, std::size_t spacial_dimensions>
void ChangeVertexValuesAround(const double& x, const double& y, std::array<bool, amount_of_vertices>& bool_array, const std::array<position_type, spacial_dimensions * amount_of_vertices>& vertex_array)
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