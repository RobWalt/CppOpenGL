# GLAD
add_library(${GLAD_LIBRARY} ${PROJECT_SOURCE_DIR}/external/glad/src/glad.c)
target_include_directories(${GLAD_LIBRARY} PUBLIC ${PROJECT_SOURCE_DIR}/external/glad/include/)
target_link_libraries(${GLAD_LIBRARY} PRIVATE ${CMAKE_DL_LIBS})

# GLFW
add_subdirectory(glfw)
add_library(${GLFW_LIBRARY} ALIAS glfw)