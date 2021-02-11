#include <array>

template <typename T, int number_of_vertices, int spatial_dimensions, int color_channels>
auto CreateInterlacedArray(std::array<T, number_of_vertices * spatial_dimensions> position_array, std::array<T, number_of_vertices * color_channels> color_array)
{
        std::array<T, position_array.size() + color_array.size()> interlaced_array;

        auto position_iterator = position_array.begin();
        auto color_iterator = color_array.begin();
        auto interlaced_iterator = interlaced_array.begin();

        for (int i = 0; i < number_of_vertices; ++i)
        {
                for (int j=0; j < spatial_dimensions; ++j)
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

