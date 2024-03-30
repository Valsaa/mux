cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR amd64)
set(CMAKE_CROSSCOMPILING TRUE)

set(CMAKE_C_COMPILER clang-cl)
set(CMAKE_C_TARGET x86_64-pc-windows-msvc)

set(CMAKE_CXX_COMPILER clang-cl)
set(CMAKE_CXX_COMPILER_TARGET x86_64-pc-windows-msvc)
set(CMAKE_MT llvm-mt-18)
set(CMAKE_RC_COMPILER llvm-rc-18)

include_directories(
    "/xwin/crt/include"
    "/xwin/sdk/include"
)

link_directories(
    "/xwin/crt/lib/x64"
    "/xwin/sdk/lib/ucrt/x64"
    "/xwin/sdk/lib/um/x64"
)

#include_directories(
#    "/home/vscode/my_msvc/VC/Tools/MSVC/14.39.33519/include"
#    "/home/vscode/my_msvc/kits/10/Include/10.0.22621.0/ucrt"
#)
#
#link_directories(
#    "/home/vscode/my_msvc/VC/Tools/MSVC/14.39.33519/lib/x64"
#    "/home/vscode/my_msvc/kits/10/Lib/10.0.22621.0/um/x64"
#    "/home/vscode/my_msvc/kits/10/Lib/10.0.22621.0/ucrt/x64"
#)



set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
