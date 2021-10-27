cmake_minimum_required(VERSION 3.14)
project(LogLib)

# indicate the documentation build
option(BUILD_DOC "Build documentation" OFF)
add_subdirectory(docs)

add_subdirectory(lib)
