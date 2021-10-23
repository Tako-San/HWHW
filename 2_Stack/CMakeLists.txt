cmake_minimum_required(VERSION 3.14)
project(StackProject)

# cool compiler flags
include(cmake/warns.cmake)

# here lies STK lib
add_subdirectory(lib)

# link STK to every tool
add_subdirectory(tools)
foreach(TOOL ${TOOLLIST})
  # add sanitizers
  target_link_options(${TOOL} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}>>")
  target_compile_options(${TOOL} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}>>")

  # specify standard
  target_compile_features(${TOOL} PRIVATE cxx_std_11)

  # include directories
  target_include_directories(${TOOL} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_include_directories(${TOOL} PRIVATE "${PROJECT_BINARY_DIR}")

  # link with STK library
  target_link_libraries(${TOOL} STK)
endforeach()
