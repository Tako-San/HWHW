cmake_minimum_required(VERSION 3.14)

# set the project name
project(TxtSort VERSION 1.1)

# indicate the documentation build
option(BUILD_DOC "Build documentation" OFF)
add_subdirectory(docs)

# add libraries
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

# include dir with Ded's warnings
include(../cmake/comp_flags.cmake)

find_package(TLL REQUIRED)
find_package(TSL REQUIRED)

# link all libraries to every tool
foreach(TOOL ${TOOLLIST})
  # add the binary tree to the search path for include files
  # so that we will find TxtSortConfig.h
  target_include_directories(${TOOL} PRIVATE "${PROJECT_BINARY_DIR}")
  target_include_directories(${TOOL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/${TOOL})
  target_include_directories(${TOOL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

  # add sanitizers
  target_link_options(${TOOL} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}>>")
  target_compile_options(${TOOL} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}>>")

  # specify standard
  target_compile_features(${TOOL} PRIVATE cxx_std_11)

  target_link_libraries(${TOOL} ${LIBLIST} TSL::TSL TLL::TLL)
endforeach()

