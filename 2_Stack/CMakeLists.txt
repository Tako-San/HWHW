cmake_minimum_required(VERSION 3.10)

# set project name
project(StackProject VERSION 0.1)

add_executable(${PROJECT_NAME} main.cc)
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_BINARY_DIR}")

add_subdirectory("${PROJECT_SOURCE_DIR}/Stack")
target_link_libraries(${PROJECT_NAME} PRIVATE StackImpl)

# specify standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

# add warnings
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

# add sanitizers
target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:Debug>:-fsanitize=address,undefined>")
target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:Debug>:-fsanitize=address,undefined>")
