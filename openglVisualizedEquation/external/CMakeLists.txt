# GLAD
add_subdirectory(glad)
add_library(${GLAD_LIBRARY} ALIAS glad)
include_directories("glfw/include/GLFW")

# GLFW
add_subdirectory(glfw)
add_library(${GLFW_LIBRARY} ALIAS glfw)