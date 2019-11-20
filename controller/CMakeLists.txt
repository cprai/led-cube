add_library(controller INTERFACE)
target_include_directories(controller INTERFACE src)
add_subdirectory(src)
target_link_libraries(controller INTERFACE pthread)
