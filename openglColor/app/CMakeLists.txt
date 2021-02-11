add_executable(${MAIN} main.cpp)
target_link_libraries(${MAIN} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${MAIN} PRIVATE ${SHADER_LIBRARY})
target_link_libraries(${MAIN} PRIVATE ${COLOR_LIBRARY})

target_include_directories(${MAIN} PRIVATE ${OPENGL_INCLUDE})
target_include_directories(${MAIN} PUBLIC ${PROJECT_BINARY_DIR})
# target_include_directories(${MAIN} PRIVATE ${PROJECT_SOURCE_DIR}/include/)
