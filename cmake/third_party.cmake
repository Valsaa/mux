include(FetchContent)

# gsl
FetchContent_Declare(
    gsl
    GIT_REPOSITORY  https://github.com/microsoft/GSL.git
    GIT_TAG         v4.0.0
    GIT_PROGRESS    TRUE
)

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

FetchContent_MakeAvailable(
    spdlog
    gsl
    cxxopts
)
