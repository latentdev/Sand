cmake_minimum_required(VERSION 3.28)
add_subdirectory("external/glad")
project(SandPhysics)

include(cmake/add-module.cmake)

set(CMAKE_CXX_STANDARD 20)

set(CPM_DOWNLOAD_VERSION 0.38.0)

if(CPM_SOURCE_CACHE)
    set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
elseif(DEFINED ENV{CPM_SOURCE_CACHE})
    set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
else()
    set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif()

if(NOT(EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
    file(DOWNLOAD
        https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
        ${CPM_DOWNLOAD_LOCATION}
    )
endif()

include(${CPM_DOWNLOAD_LOCATION})

CPMAddPackage("gh:g-truc/glm#master")
CPMAddPackage("gh:gabime/spdlog#v1.11.0")
CPMAddPackage("gh:jeremy-rifkin/libassert#v1.1")
CPMAddPackage("gh:hanickadot/compile-time-regular-expressions#main")

CPMAddPackage(
    NAME GLFW
    GITHUB_REPOSITORY glfw/glfw
    GIT_TAG 3.3.8
    OPTIONS
    "GLFW_BUILD_TESTS OFF"
    "GLFW_BUILD_EXAMPLES OFF"
    "GLFW_BULID_DOCS OFF"
)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG "origin/master"
)
if(NOT imgui_POPULATED)
  FetchContent_MakeAvailable(imgui)

    add_library(imgui
        STATIC
        "${imgui_SOURCE_DIR}/imgui.cpp"
        "${imgui_SOURCE_DIR}/imgui_demo.cpp"
        "${imgui_SOURCE_DIR}/imgui_draw.cpp"
        "${imgui_SOURCE_DIR}/imgui_tables.cpp"
        "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
        "${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp"
    )

    target_include_directories(imgui
        PUBLIC
        ${imgui_SOURCE_DIR}
    )
endif()

#Create Module
RAOE_ADD_MODULE(STATIC
                NAME "sand-core"
                NAMESPACE "nick"
                INCLUDE_DIRECTORIES
                PUBLIC
                    "src"
                CPP_SOURCE_FILES #Add all cpp files
                "src/OpenGLRenderer.cpp"
                "src/PhysicsEngine.cpp"
                "src/WorldState.cpp"
                "src/Simulator.cpp"
                "src/SpacialHash.cpp"
                DEPENDENCIES
                PUBLIC
                    spdlog
                    assert
                    glm::glm
                    ctre::ctre
                    glfw
                    imgui
                    glad
)

add_executable(SandPhysics src/main.cpp)  # Replace main.cpp with your source files

target_link_libraries(SandPhysics nick::sand-core)