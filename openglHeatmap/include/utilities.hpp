#include <filesystem>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

class ShaderSourceCode
{
public:
  unsigned int program_id_;
  ShaderSourceCode(const std::filesystem::path & vertex_shader_file_name_,
		   const std::filesystem::path & fragment_shader_file_name_);
  void use();
  void SetUniform(const float & value, const char* name);
private:
  void CheckCompileErrors(unsigned int, std::string);
}; // class ShaderSourceCode
