#include <array>
#include <iostream>
#include <stdexcept>

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

template <typename Type, std::size_t size>
void PrintArray(const std::array<Type, size> & array)
{
		for(auto e: array)
		{
						std::cout << e << ",";
		}
		std::cout << std::endl;
}
