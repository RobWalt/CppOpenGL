#pragma once

#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <optional>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
std::optional<std::array<float,2>> processMouseInput(GLFWwindow *window, bool& eventShouldTrigger);
std::array<double, 2> PixelCoordsToVertexCoords(double x_pix, double y_pix, unsigned int window_width, unsigned int window_height);

class ShaderSourceCode
{
public:
  unsigned int program_id_;
  ShaderSourceCode(const std::filesystem::path & vertex_shader_file_name_,
		   const std::filesystem::path & fragment_shader_file_name_);
  void use();
  void SetUniform(const float & value, const char* name);
  void SetUniform(const int & value, const char* name);
private:
  void CheckCompileErrors(unsigned int, std::string);
}; // class ShaderSourceCode
