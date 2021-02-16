#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

#include "utilities.hpp"

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

ShaderSourceCode::ShaderSourceCode(
	const std::filesystem::path & vertex_shader_file_name_,
	const std::filesystem::path & fragment_shader_file_name_)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertex_code{};
	std::string fragment_code{};
	std::ifstream vertex_shader_file;
	std::ifstream fragment_shader_file;

	// ensure ifstream objects can throw exceptions:
	vertex_shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fragment_shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try
	{
        // open files
        vertex_shader_file.open(vertex_shader_file_name_);
        fragment_shader_file.open(fragment_shader_file_name_);
        std::stringstream vertex_shader_stream, fragment_shader_stream;
        // read file's buffer contents into streams
        vertex_shader_stream << vertex_shader_file.rdbuf();
        fragment_shader_stream << fragment_shader_file.rdbuf();
        // close file handlers
        vertex_shader_file.close();
        fragment_shader_file.close();
        // convert stream into string
        vertex_code   = vertex_shader_stream.str();
        fragment_code = fragment_shader_stream.str();
	}
	catch(std::ifstream::failure e)
	{
	std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* v_shader_code = vertex_code.c_str();
	const char* f_shader_code = fragment_code.c_str();

	unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex_shader_id, 1, &v_shader_code, NULL);
	glShaderSource(fragment_shader_id, 1, &f_shader_code, NULL);

	glCompileShader(vertex_shader_id);
	glCompileShader(fragment_shader_id);

	CheckCompileErrors(vertex_shader_id, "VERTEX");
	CheckCompileErrors(fragment_shader_id, "FRAGMENT");

	program_id_ = glCreateProgram();
	glAttachShader(program_id_,vertex_shader_id);
	glAttachShader(program_id_,fragment_shader_id);
	glLinkProgram(program_id_);
	CheckCompileErrors(program_id_, "PROGRAM");

	glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);
}

void ShaderSourceCode::CheckCompileErrors(unsigned int shader, std::string type)
    // utility function for checking shader compilation/linking errors.
{
        GLint success;
        GLchar info_log[1024];
        if(type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, info_log);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, info_log);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
} // void CheckCompileError(...)

void ShaderSourceCode::use()
{
	glUseProgram(program_id_);
}

void ShaderSourceCode::SetUniform(const float & value, const char* name)
{
	unsigned int location_uniform  =  glGetUniformLocation(program_id_, name);
	glUniform1f(location_uniform, value);
}

void ShaderSourceCode::SetUniform(const int & value, const char* name)
{
	unsigned int location_uniform  =  glGetUniformLocation(program_id_, name);
	glUniform1i(location_uniform, value);
}
