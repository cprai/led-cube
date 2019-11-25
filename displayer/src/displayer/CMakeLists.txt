target_sources(displayer INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/am335x/app_loader/include/prussdrv.h
    ${CMAKE_CURRENT_SOURCE_DIR}/am335x/app_loader/include/pruss_intc_mapping.h
    ${CMAKE_CURRENT_SOURCE_DIR}/am335x/app_loader/interface/prussdrv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/color.h
    ${CMAKE_CURRENT_SOURCE_DIR}/displayer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/util.h
    ${CMAKE_CURRENT_SOURCE_DIR}/util.c
    ${CMAKE_CURRENT_SOURCE_DIR}/pru.h
    ${CMAKE_CURRENT_SOURCE_DIR}/pru.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ledscape.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ledscape.h

)
