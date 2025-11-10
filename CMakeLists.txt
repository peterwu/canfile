cmake_minimum_required(VERSION 3.16)

project(canfile VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_WEB_ASSETS_DIR ${PROJECT_BINARY_DIR}/assets/web)

add_subdirectory(core)
add_subdirectory(web)

add_dependencies(main web)