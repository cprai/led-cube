cmake_minimum_required(VERSION 3.10)
project(led-cube)

# No in-source build
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "In-source builds are not allowed.")
endif("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -fno-rtti")
set(CMAKE_CXX_FLAGS_DEBUG 
    "-O0 -g -fsanitize=address,undefined -fno-omit-frame-pointer"
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(renderer)

add_executable(main main.cpp)
target_link_libraries(main renderer)
