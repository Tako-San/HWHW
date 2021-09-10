cmake_minimum_required(VERSION 3.10)

# set the project name
project(SqEq VERSION 1.0)

# configure header for version print
configure_file(SqEqConfig.h.in SqEqConfig.h)

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

# add the executable
add_executable(SqEq main.cc SqEq.cc)

# add the binary tree to the search path for include files
# so that we will find SqEqConfig.h
target_include_directories(SqEq PUBLIC "${PROJECT_BINARY_DIR}")

# add warnings and sanitizers
target_compile_options(SqEq INTERFACE "-Wall -Wextra -fsanitize=addres,undefined")
