set(RUST_INPUT pru_module.rs)
set(RUST_OUTPUT libpru_module.so)

EXECUTE_PROCESS(
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND cargo build --target=armv7-unknown-linux-gnueabihf --target-dir=${CMAKE_CURRENT_BINARY_DIR}/
)

TARGET_LINK_LIBRARIES(displayer INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/armv7-unknown-linux-gnueabihf/debug/${RUST_OUTPUT})

