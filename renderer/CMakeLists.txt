add_library(renderer INTERFACE)
target_sources(renderer INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/file/objParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/geometry/matrix3D.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/geometry/transformation.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/geometry/triangle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/geometry/vector3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/geometry/vertex.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/entity.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/mesh.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/renderer.h
)
target_include_directories(renderer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)
