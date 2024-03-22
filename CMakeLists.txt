# CMake version is 3.20 to be able to use C++ 23
# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
cmake_minimum_required(VERSION 3.20)

# Project name
project(mux)

# Project directories
get_filename_component(root_dir ${CMAKE_CURRENT_SOURCE_DIR} REALPATH)
message("-- root_dir is ${root_dir}")
cmake_path(APPEND cmake_dir ${root_dir} "cmake")
cmake_path(APPEND src_dir ${root_dir} "src")
cmake_path(APPEND bin_dir ${CMAKE_CURRENT_BINARY_DIR} "bin")

include("${cmake_dir}/third_party.cmake")
include("${cmake_dir}/utils.cmake")
message("-- Custom CMake files included")

# Mux target
file(GLOB SOURCES "${src_dir}/*.cpp")
add_executable(mux ${SOURCES})
target_compile_features(mux PRIVATE cxx_std_23)
target_link_libraries(mux
    PRIVATE
    spdlog::spdlog
    cxxopts
)
_set_compilers_options(mux)
