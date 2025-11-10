set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include(FetchContent)

# cpp-httplib
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.27.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(httplib)

# fltk
FetchContent_Declare(
    fltk
    GIT_REPOSITORY https://github.com/fltk/fltk.git
    GIT_TAG release-1.4.4
    GIT_SHALLOW TRUE
)

set(FLTK_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(FLTK_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(fltk)

# webview
FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview
    GIT_TAG 0.12.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(webview)

if(APPLE)
    set(PLATFORM_SOURCES menu.mm)
    set(PLATFORM_LIBS "-framework Cocoa" "-framework WebKit")
endif()

add_executable(main
    main.cpp
    ${PLATFORM_SOURCES}
)

target_link_libraries(main PRIVATE
    fltk::fltk
    httplib::httplib
    webview::core
    ${PLATFORM_LIBS}
)

set(PROJECT_WEB_ASSETS_DIR ${PROJECT_BINARY_DIR}/assets/web)

target_compile_definitions(main PRIVATE WEB_ASSETS_DIR="${PROJECT_WEB_ASSETS_DIR}")

# copy web assets after build
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_WEB_DIR}/dist/web/browser ${PROJECT_WEB_ASSETS_DIR}
)
