# MyLib Library
set(LIBRARY_SOURCES "my_lib.cpp")
set(LIBRARY_INCLUDES "${PROJECT_SOURCE_DIR}/include/")
add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_INCLUDES})
target_link_libraries(${LIBRARY_NAME} PUBLIC ${LIBRARY_LOG})
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_17)
target_set_warnings(TARGET ${LIBRARY_NAME} ENABLE ON AS_ERROR ON)

# Vertex Library
set(LIBRARY_VERTEX_SOURCES "vertexshader.cpp")
set(LIBRARY_VERTEX_INCLUDES 
        "${PROJECT_SOURCE_DIR}/include/"
    )
add_library(${LIBRARY_VERTEXSHADER} ${LIBRARY_VERTEX_SOURCES})
target_include_directories(${LIBRARY_VERTEXSHADER} PUBLIC ${LIBRARY_VERTEX_INCLUDES})
target_link_libraries(${LIBRARY_VERTEXSHADER} PUBLIC ${OPENGL_LIBS})
target_compile_features(${LIBRARY_VERTEXSHADER} PUBLIC cxx_std_17)
target_set_warnings(TARGET ${LIBRARY_VERTEXSHADER} ENABLE ON AS_ERROR ON)

# Vertex Library
set(LIBRARY_PHYSICS_SOURCES "physics.cpp")
set(LIBRARY_PHYSICS_INCLUDES 
        "${PROJECT_SOURCE_DIR}/include/"
    )
add_library(${LIBRARY_PHYSICS} ${LIBRARY_PHYSICS_SOURCES})
target_include_directories(${LIBRARY_PHYSICS} PUBLIC ${LIBRARY_PHYSICS_INCLUDES})
target_link_libraries(${LIBRARY_PHYSICS} PUBLIC ${OPENGL_LIBS})
target_compile_features(${LIBRARY_PHYSICS} PUBLIC cxx_std_17)
target_set_warnings(TARGET ${LIBRARY_PHYSICS} ENABLE ON AS_ERROR ON)


