#include <iostream>
#include <stdio.h>

#include "my_lib.hpp"

bool print_hello_world()
{
    printf("Printf: Hello World\n");

    return true;
}

bool cout_hello_world()
{
    std::cout << "Cout: Hello World" << std::endl;

    return true;
}

std::int32_t compute_average(std::int32_t a, std::int32_t b)
{
    return (a + b) / 2;
}
