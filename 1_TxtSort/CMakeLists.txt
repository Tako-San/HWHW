cmake_minimum_required(VERSION 3.10)

# set the project name
project(TxtSort VERSION 1.1)

# indicate the documentation build
option(BUILD_DOC "Build documentation" OFF)
add_subdirectory(Docs)

# add the executable
add_executable(TxtSort main.cc)

# add libraries
add_subdirectory(TSL)
add_subdirectory(TSL/CharBuf)
add_subdirectory(Trace)
add_subdirectory(FileSys)
add_subdirectory(Qsort)

target_link_libraries(TxtSort PRIVATE TLL TSL TFL TQS)

# add the binary tree to the search path for include files
# so that we will find TxtSortConfig.h
target_include_directories(TxtSort PRIVATE "${PROJECT_BINARY_DIR}")

# specify standard
target_compile_features(TxtSort PRIVATE cxx_std_11)

# include dir with Ded's warnings
include(cmake/warns.cmake)

# add warnings
target_compile_options(TxtSort PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_GCC_WARNS_LST}>>")

# add sanitizers
target_link_options(TxtSort PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}>>")
target_compile_options(TxtSort PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}>>")
