# THIS IS A HEADER ONLY EXTERNAL LIB EXAMPLE
#set(LIBRARY_INCLUDES "linalg/")
#add_library(${LIBRARY_LINALG} INTERFACE)
#target_include_directories(${LIBRARY_LINALG} SYSTEM INTERFACE ${LIBRARY_INCLUDES})
#target_set_warnings(TARGET ${LIBRARY_LINALG} ENABLE OFF AS_ERROR OFF)

# Loguru
file(GLOB LOGURU_SOURCES "loguru/*.cpp")
add_library(${LIBRARY_LOG} STATIC ${LOGURU_SOURCES})
target_include_directories(${LIBRARY_LOG} PUBLIC loguru)
if(UNIX)
    target_link_libraries(${LIBRARY_LOG} PUBLIC pthread dl)
endif()
target_set_warnings(TARGET ${LIBRARY_LOG} ENABLE OFF AS_ERROR OFF)

# Celero
if(USE_BENCHMARKS)
    add_subdirectory(Celero)
    target_set_warnings(TARGET celero ENABLE OFF AS_ERROR OFF)
    add_library(${LIBRARY_BENCH} ALIAS celero)
endif()

# GLFW
# This was suggested by 
# https://www.glfw.org/docs/latest/build_guide.html
# dunno if needed
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# the real stuff
add_subdirectory(glfw)
target_set_warnings(TARGET glfw ENABLE OFF AS_ERROR OFF)
add_library(${LIBRARY_GLFW} ALIAS glfw)

# GLM
add_subdirectory(glm)
target_set_warnings(TARGET glm ENABLE OFF AS_ERROR OFF)
add_library(${LIBRARY_GLM} ALIAS glm)

# GLAD
add_subdirectory(glad)
target_set_warnings(TARGET glad ENABLE OFF AS_ERROR OFF)
add_library(${LIBRARY_GLAD} ALIAS glad)

# gtest
add_subdirectory(googletest)
target_set_warnings(TARGET gtest ENABLE OFF AS_ERROR OFF)
add_library(${LIBRARY_GTEST} ALIAS gtest)


