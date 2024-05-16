cmake_minimum_required(VERSION 3.28)
project(SandPhysics)

set(CMAKE_CXX_STANDARD 20)

# Add GLFW
add_subdirectory(external/glfw)
# Add glm
add_subdirectory(external/glm)

add_library(glad STATIC external/glad/src/gl.c)
target_include_directories(glad PRIVATE external/glad/include)

add_executable(SandPhysics src/main.cpp)  # Replace main.cpp with your source files

#target_link_libraries(SandPhysics glfw)
#target_link_libraries(SandPhysics glm)
target_link_libraries(SandPhysics glfw glm glad)
#target_include_directories(SandPhysics PRIVATE external/glfw/include)
#target_include_directories(SandPhysics PRIVATE external/glm/glm)
target_include_directories(SandPhysics PRIVATE external/glfw/include external/glad/include external/glm/glm)