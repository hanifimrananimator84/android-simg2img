project(libsparse LANGUAGES CXX)

add_library(libsparse STATIC 
    src/sparse.cpp
    src/utils.cpp
    src/crc32.cpp
)

target_include_directories(libsparse PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(libsparse PUBLIC cxx_std_17)