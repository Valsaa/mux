cmake_minimum_required(VERSION 3.18)

project(server LANGUAGES CXX)

file(GLOB SOURCES *.cpp)

include(FetchContent)

# gsl
FetchContent_Declare(
    gsl
    GIT_REPOSITORY  https://github.com/microsoft/GSL.git
    GIT_TAG         v4.0.0
    GIT_PROGRESS    TRUE
    SYSTEM
)

# spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog.git
    GIT_TAG         v1.12.0
    GIT_PROGRESS    TRUE
    SYSTEM
)

FetchContent_MakeAvailable(
    spdlog
    gsl
)

add_executable(server ${SOURCES})
target_link_libraries(server
    PRIVATE
    spdlog::spdlog
    Microsoft.GSL::GSL
)
