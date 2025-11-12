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
    if(HOMEBREW_LLVM_PREFIX)
        if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64")
            set(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES "")
        endif()

        set(HOMEBREW_LIBCXX_INC ${HOMEBREW_LLVM_PREFIX}/include/c++/v1)
        set(HOMEBREW_LIBCXX_LIB ${HOMEBREW_LLVM_PREFIX}/lib/c++)
    endif()

    set(PLATFORM_SOURCES menu.mm)
    set(PLATFORM_LIBS "-framework Cocoa" "-framework WebKit")
endif()

add_executable(main
    main.cpp
    ${PLATFORM_SOURCES}
)

if(HOMEBREW_LLVM_PREFIX)
    target_include_directories(main SYSTEM PRIVATE ${HOMEBREW_LIBCXX_INC})
    target_link_directories(main PRIVATE ${HOMEBREW_LIBCXX_LIB})
endif()

target_link_libraries(main PRIVATE
    httplib::httplib
    webview::core
    ${PLATFORM_LIBS}
)

target_compile_definitions(main PRIVATE
    WEB_ASSETS_DIR="${PROJECT_WEB_ASSETS_DIR}")
