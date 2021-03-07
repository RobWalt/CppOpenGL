#include <array>
#include <stdexcept>
#include <algorithm>

template <std::size_t grid_width, std::size_t grid_height>
std::array<INDEX_TYPE, (grid_width-1)*(grid_height-1)*3> CreateUpperTriangleIndices()
{
    std::array<INDEX_TYPE, (grid_width-1)*(grid_height-1)*3> upper_triangle_indices;
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

template <std::size_t grid_width, std::size_t grid_height>
std::array<INDEX_TYPE, (grid_width-1)*(grid_height-1)*3> CreateLowerTriangleIndices()
{
    std::array<INDEX_TYPE, (grid_width-1)*(grid_height-1)*3> upper_triangle_indices;
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

template<typename T, std::size_t N, std::size_t M>
auto ConcatenateArrays(const std::array<T, N>& array1, const std::array<T, M>& array2)
{
    std::array<T, N+M> result;
    std::copy (array1.cbegin(), array1.cend(), result.begin());
    std::copy (array2.cbegin(), array2.cend(), result.begin() + N);
    return result;
}

template<std::size_t grid_width, std::size_t grid_height>
std::array<INDEX_TYPE,(grid_width-1)*(grid_height-1)*2*3>CreateTriangleIndices(){
		constexpr std::size_t amount_of_triangles = (grid_width-1)*(grid_height-1);
		std::array<INDEX_TYPE,amount_of_triangles*2*3> result;
		// Create upper triangle indices
		auto lower_triangle_indices = CreateLowerTriangleIndices<grid_width, grid_height>();
		auto upper_triangle_indices = CreateUpperTriangleIndices<grid_width, grid_height>();
		result = ConcatenateArrays(lower_triangle_indices,upper_triangle_indices);
    return result;
}

template<std::size_t N>
Heatmap<N>::Heatmap(const Grid<N> & grid, const Indice_array<N>& indices):
				data_{}
{
    auto [VAO,VBO, EBO] = LoadVertexData(3,{0,1,2},{Expand(grid), {1.0f}},{0,1});
}


//template<std::size_t number_of_vertices, std::size_t number_of_triangles>
//Heatmap<number_of_vertices>::Heatmap(
//								const Grid<number_of_vertices> & grid,
//							 	const std::array<INDEX_TYPE,3*number_of_triangles> indices
//								const Gluint grid_width;
//								const Gluint grid_height;
//								)
//				: data_{}
//{
//	std::array<INDEX_TYPE, amount_of_triangles * 3> triangle_indices;
//}

// API possibility for CreatePositionArray
//
//(const DomainType<N> & data,
//							 	const Position & upper_left_corner,
//								const Position & lower_right_corner,
//								const PrecisionType grid_width, 
//								const PrecisionType grid_height)
