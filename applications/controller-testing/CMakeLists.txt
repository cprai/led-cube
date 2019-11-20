set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/controller-testing)
add_executable(controller-testing main.cpp)
target_link_libraries(controller-testing controller displayer)
