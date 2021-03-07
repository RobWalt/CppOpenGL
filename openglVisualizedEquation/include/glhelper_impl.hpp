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

template<typename T, std::size_t N, std::size_t M>
auto ConcatenateArrays(const std::array<T, N>& array1, const std::array<T, M>& array2)
{
    std::array<T, N+M> result;
    std::copy (array1.cbegin(), array1.cend(), result.begin());
    std::copy (array2.cbegin(), array2.cend(), result.begin() + N);
    return result;
}

template<std::size_t N>
Heatmap<N>::Heatmap(const DomainType<N> & data):data_(data){
}
