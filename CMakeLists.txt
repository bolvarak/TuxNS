include_directories(/opt/Qt/5.5/gcc_64/include)
link_directories(/opt/Qt/5.5/gcc_64/lib)

cmake_minimum_required(VERSION 3.3)
project(TuxNS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES source/api/main.cpp)
add_executable(TuxNS ${SOURCE_FILES})