# =============================================
# android-simg2img v4.1 (2021) - Main Build Config
# =============================================
cmake_minimum_required(VERSION 3.12)
project(android-simg2img 
    VERSION 4.1.0 
    LANGUAGES C CXX
)

# Configuration options
option(BUILD_TOOLS "Build command-line tools" ON)
option(BUILD_TESTS "Build test suite" OFF)
option(INSTALL_LIBS "Install library components" ON)

# Core library first
add_subdirectory(libsparse)

# Tool builds
if(BUILD_TOOLS)
    # simg2img (sparse → raw)
    add_executable(simg2img src/tools/simg2img.cpp)
    target_link_libraries(simg2img libsparse)
    target_compile_features(simg2img PRIVATE cxx_std_17)
    set_target_properties(simg2img PROPERTIES OUTPUT_NAME "simg2img")

    # img2simg (raw → sparse)
    add_executable(img2simg src/tools/img2simg.cpp)
    target_link_libraries(img2simg libsparse)
    target_compile_features(img2simg PRIVATE cxx_std_17)

    # imgdisplay (TUI viewer)
    find_package(Curses REQUIRED)
    add_executable(imgdisplay src/tools/imgdisplay.cpp)
    target_link_libraries(imgdisplay libsparse ${CURSES_LIBRARIES})
    target_include_directories(imgdisplay PRIVATE ${CURSES_INCLUDE_DIRS})
endif()

# Installation
if(INSTALL_LIBS)
    install(TARGETS libsparse
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
    )

    install(DIRECTORY libsparse/include/sparse
        DESTINATION include
    )
endif()

if(BUILD_TOOLS AND INSTALL_LIBS)
    install(TARGETS simg2img img2simg imgdisplay
        RUNTIME DESTINATION bin
    )
endif()

# Testing
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Package generation
include(CMakePackageConfigHelpers)
configure_package_config_file(
    cmake/android-simg2img-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/android-simg2img-config.cmake
    INSTALL_DESTINATION lib/cmake/android-simg2img
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/android-simg2img-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/android-simg2img-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/android-simg2img-config-version.cmake
    DESTINATION lib/cmake/android-simg2img
)