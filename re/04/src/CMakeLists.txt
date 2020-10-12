cmake_minimum_required(VERSION 3.16)
project(EzVM)

set(CMAKE_CXX_STANDARD 20)
set(TARGET_NAME EzVM)

add_executable(${TARGET_NAME} main.cpp instruction.h program.h)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC" AND CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_options(${TARGET_NAME} PRIVATE /Zi)

    # Tell linker to include symbol data
    set_target_properties(${TARGET_NAME} PROPERTIES
            LINK_FLAGS "/INCREMENTAL:NO /DEBUG /OPT:REF /OPT:ICF"
            )

    # Set file name & location
    set_target_properties(${TARGET_NAME} PROPERTIES
            COMPILE_PDB_NAME ${TARGET_NAME}
            COMPILE_PDB_OUTPUT_DIR ${CMAKE_BINARY_DIR}
            )
endif()

