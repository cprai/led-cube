add_library(renderer INTERFACE)
target_include_directories(renderer INTERFACE src)
target_link_libraries(renderer INTERFACE displayer)
add_subdirectory(src)
