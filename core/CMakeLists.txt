set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include(FetchContent)

# asio
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-36-0
)
FetchContent_MakeAvailable(asio)

set(ASIO_INCLUDE_DIR ${asio_SOURCE_DIR}/asio/include)

# crowcpp
FetchContent_Declare(
    crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG v1.3.0
)
FetchContent_MakeAvailable(crow)

# webview
FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview
    GIT_TAG 0.12.0)
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
    webview::core
    Crow::Crow
    ${PLATFORM_LIBS}
)

set(PROJECT_WEB_ASSETS_DIR ${PROJECT_BINARY_DIR}/assets/web)

target_compile_definitions(main PRIVATE WEB_ASSETS_DIR="${PROJECT_WEB_ASSETS_DIR}")

# copy web assets after build
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_WEB_DIR}/dist/web/browser ${PROJECT_WEB_ASSETS_DIR}
)
