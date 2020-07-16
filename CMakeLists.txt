cmake_minimum_required(VERSION 3.15)
project(webmaster)

set(CMAKE_CXX_STANDARD 17)

include_directories(inc)

add_subdirectory(src)
add_subdirectory(tests)