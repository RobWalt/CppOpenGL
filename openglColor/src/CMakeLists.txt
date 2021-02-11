# compile shader
add_library(${SHADER_LIBRARY} shader.cpp)
target_include_directories(${SHADER_LIBRARY} PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_include_directories(${SHADER_LIBRARY} PRIVATE ${OPENGL_INCLUDE})
target_link_libraries(${SHADER_LIBRARY} PRIVATE ${OPENGL_LIBRARIES})

# compile color
add_library(${COLOR_LIBRARY} color_palette.cc)
target_include_directories(${COLOR_LIBRARY} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

# compile utilities
add_library(${UTILITIES_LIBRARY} utilities.cpp)
target_include_directories(${UTILITIES_LIBRARY} PUBLIC ${PROJECT_SOURCE_DIR}/include/)
