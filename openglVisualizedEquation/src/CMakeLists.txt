set(UTILITY_SOURCES "utilities.cpp")
set(UTILITY_INCLUDES "${PROJECT_SOURCE_DIR}/include/")
add_library(${UTILITY_LIB} OBJECT ${UTILITY_SOURCES})
target_include_directories(${UTILITY_LIB} PUBLIC ${UTILITY_INCLUDES})
target_compile_features(${UTILITY_LIB} PUBLIC cxx_std_17)

set(GLHELPER_SOURCES "glhelper.cpp")
set(GLHELPER_INCLUDES "${PROJECT_SOURCE_DIR}/include/")
add_library(${GLHELPER_LIB} OBJECT ${GLHELPER_SOURCES})
target_include_directories(${GLHELPER_LIB} PUBLIC ${GLHELPER_INCLUDES})
target_compile_features(${GLHELPER_LIB} PUBLIC cxx_std_17)

# Equation solver Library
set(LIBRARY_PHYSICS_SOURCES "physics.cpp")
set(LIBRARY_PHYSICS_INCLUDES "${PROJECT_SOURCE_DIR}/include/")
add_library(${LIBRARY_PHYSICS} OBJECT ${LIBRARY_PHYSICS_SOURCES})
target_include_directories(${LIBRARY_PHYSICS} PUBLIC ${LIBRARY_PHYSICS_INCLUDES})
target_compile_features(${LIBRARY_PHYSICS} PUBLIC cxx_std_17)