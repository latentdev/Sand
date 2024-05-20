cmake_minimum_required(VERSION 3.28)
project(SandPhysics)

set(CMAKE_CXX_STANDARD 20)

set(GLAD_EXT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/glad/src")
set(GLAD_EXT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/glad/include")
add_library(glad "${GLAD_EXT_INCLUDE_DIR}/glad/gl.h" "${GLAD_EXT_SOURCE_DIR}/gl.c" "src/PhysicsEngine.cpp")
target_include_directories(glad PUBLIC "${GLAD_EXT_INCLUDE_DIR}")
message(STATUS "glad include dir: ${GLAD_EXT_INCLUDE_DIR}")
message(STATUS "glad source dir: ${GLAD_EXT_SOURCE_DIR}")
message(STATUS "glad: ${glad}")
# Add GLFW
add_subdirectory(external/glfw)
# Add glm
add_subdirectory(external/glm)

#add_library(glad STATIC external/glad/gl.c)
#target_include_directories(glad PRIVATE external/glad/include)

add_executable(SandPhysics src/main.cpp)  # Replace main.cpp with your source files

#target_link_libraries(SandPhysics glfw)
#target_link_libraries(SandPhysics glm)
target_link_libraries(SandPhysics glfw glm glad)
#target_include_directories(SandPhysics PRIVATE external/glfw/include)
#target_include_directories(SandPhysics PRIVATE external/glm/glm)
target_include_directories(SandPhysics PRIVATE external/glfw/include external/glm/glm)