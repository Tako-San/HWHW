cmake_minimum_required(VERSION 3.14)

# set the project name
project(MathProject VERSION 1.2)

# configure header for version print
configure_file(SqEqConfig.hh.in SqEqConfig.hh)

# indicate the documentation build
option(BUILD_DOC "Build documentation" OFF)
add_subdirectory(docs)

# adding sources
add_subdirectory(lib)

# collecting tools
add_subdirectory(tools)
message(STATUS "Collected tools: ${TOOLLIST}")

# link all libraries to every tool - just in case
foreach(TOOL ${TOOLLIST})
  target_link_libraries(${TOOL} SqEq)
  install(TARGETS ${TOOL} DESTINATION bin)
endforeach()

install()
