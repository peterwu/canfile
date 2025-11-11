cmake_minimum_required(VERSION 3.16)

if(APPLE)
    execute_process(
        COMMAND brew --prefix llvm
        OUTPUT_VARIABLE HOMEBREW_LLVM_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )

    if(HOMEBREW_LLVM_PREFIX)
        set(CMAKE_C_COMPILER "${HOMEBREW_LLVM_PREFIX}/bin/clang")
        set(CMAKE_CXX_COMPILER "${HOMEBREW_LLVM_PREFIX}/bin/clang++")
    endif()
endif()

project(canfile VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_WEB_ASSETS_DIR ${PROJECT_BINARY_DIR}/assets/web)

add_subdirectory(core)
add_subdirectory(web)

add_dependencies(main web)