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

using namespace glm;

int main( void )
{
        GLFWwindow* window;
        // Initialise GLFW
        if( !glfwInit() )
        {
                fprintf( stderr, "Failed to initialize GLFW\n" );
                getchar();
                return -1;
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Open a window and create its OpenGL context
        window = glfwCreateWindow( 1024, 768, "Playground", NULL, NULL);
        if( window == NULL ){
                fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
                getchar();
                glfwTerminate();
                return -1;
        }
        glfwMakeContextCurrent(window);

        // Initialize GLAD
        if(!gladLoadGL()) {
                fprintf(stderr, "Failed to initialize GLAD\n");
                getchar();
                glfwTerminate();
                return -1;
        }
        printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

        // Dark blue background
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        do{
                glClear(GL_COLOR_BUFFER_BIT);

                // Draw nothing, see you in tutorial 2 !

                // Swap buffers
                glfwSwapBuffers(window);
                glfwPollEvents();

        } // Check if the ESC key was pressed or the window was closed
        while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                   glfwWindowShouldClose(window) == 0 );

        // Close OpenGL window and terminate GLFW
        glfwTerminate();

        return 0;
}

/*
int main(int argc, char **argv)
{
    std::cout << PROJECT_VERSION_MAJOR << "."
              << PROJECT_VERSION_MINOR << "."
              << PROJECT_VERSION_PATCH << std::endl;

    cout_hello_world();
    print_linalg_vector();
    print_boost_version();

    loguru::init(argc, argv);
    LOG_F(INFO, "Hello from main!");

    // int i = 128000;
    // short j = i;

    return 0;
}
*/