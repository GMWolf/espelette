cmake_minimum_required(VERSION 3.21)
project(espelette)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glad)
add_subdirectory(external/glm)
include(cmake/glfw.cmake)
include(cmake/stb.cmake)

add_subdirectory(espelette)

add_executable(test main.cpp)
target_link_libraries(test PRIVATE espelette)