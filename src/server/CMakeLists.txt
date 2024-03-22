cmake_minimum_required(VERSION 3.18)

project(server LANGUAGES CXX)

file(GLOB SOURCES *.cpp)

add_executable(server ${SOURCES})
