include(FetchContent)

# spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog.git
    GIT_TAG         v1.12.0
    GIT_PROGRESS    TRUE
)

# cxxopts
FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY  https://github.com/jarro2783/cxxopts.git
    GIT_TAG         v3.2.0
    GIT_PROGRESS    TRUE
)

# googletest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(
    spdlog
    cxxopts
    googletest
)
