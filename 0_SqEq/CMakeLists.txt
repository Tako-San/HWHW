cmake_minimum_required(VERSION 3.10)

# set the project name
project(SqEq VERSION 1.0)

configure_file(SqEqConfig.h.in SqEqConfig.h)

# add the executable
add_executable(SqEq main.c SqEq.c)


# add the binary tree to the search path for include files
# so that we will find SqEqConfig.h
target_include_directories(SqEq PUBLIC "${PROJECT_BINARY_DIR}")

# add warnings and sanitizers
target_compile_options(SqEq INTERFACE "-Wall -Wextra -fsanitize=addres,undefined")