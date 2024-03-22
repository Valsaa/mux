cmake_minimum_required(VERSION 3.18)

project(client LANGUAGES CXX)

file(GLOB SOURCES *.cpp)

add_executable(client ${SOURCES})
