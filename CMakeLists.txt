cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

project(opengl-tutorial)

add_subdirectory(externals)

add_executable(gl src/main.cpp)
target_include_directories(gl PRIVATE include)
target_link_libraries(gl
	PUBLIC glad
)