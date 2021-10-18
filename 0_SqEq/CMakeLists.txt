cmake_minimum_required(VERSION 3.14)


# set the project name
project(MathProject VERSION 1.2)

# configure header for version print
configure_file(SqEqConfig.hh.in SqEqConfig.hh)

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


# collecting libs
add_subdirectory(lib)
message(STATUS "Collected libs: ${LIBLIST}")

# common includes
foreach(LIB ${LIBLIST})
  target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIB})
  target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endforeach()


# collecting tools
add_subdirectory(tools)
message(STATUS "Collected tools: ${TOOLLIST}")

# link all libraries to every tool -- just in case
foreach(TOOL ${TOOLLIST})
  target_include_directories(${TOOL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/${TOOL})
  target_include_directories(${TOOL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_link_libraries(${TOOL} ${LIBLIST})
  install(TARGETS ${TOOL} DESTINATION bin)
endforeach()


install()
