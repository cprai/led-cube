add_library(displayer INTERFACE)
target_include_directories(displayer INTERFACE src)
add_subdirectory(src)
target_link_libraries(displayer INTERFACE pthread dl)
