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

# webview
FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview.git
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
    httplib::httplib
    webview::core
    ${PLATFORM_LIBS}
)

target_compile_definitions(main PRIVATE WEB_ASSETS_DIR="${PROJECT_WEB_ASSETS_DIR}")
