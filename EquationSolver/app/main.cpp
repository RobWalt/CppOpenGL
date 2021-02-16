// ----------- Template Stuff
#include <iostream>

#include "my_lib.hpp"
#include "loguru.hpp"

#include "ProjectConfig.h"
// ------------

// OpenGL Boilerplate Code Stuff
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "my_glm.hpp"
#include "vertexshader.hpp"
#include "physics.hpp"

using namespace glm;
 
int main( void )
{
    constexpr float c = 1.0f;
    constexpr float dx = 1.0f;
    constexpr float dt = 0.1f * (dx * dx);
    DifferentialEquation DEQ{c,dx,dt};
    DEQ.print_solution();
    for (auto i=0; i<10; i++)
    {
        DEQ.solver_step();
    }
    std::cout << "========" << std::endl;
    DEQ.print_solution();

    std::cout << "Success" << std::endl;

    return 0;
}