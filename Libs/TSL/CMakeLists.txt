cmake_minimum_required(VERSION 3.14)

project(TakoStrLib)

# indicate the documentation build
option(BUILD_DOC "Build documentation" OFF)
add_subdirectory(docs)

# TSL - Tako's string library
add_library(TSL tsl.cc)

# link with CB library
add_subdirectory(CharBuf)
target_link_libraries(TSL CB)

# link with TLL library
find_package(TLL REQUIRED)
target_link_libraries(TSL TLL::TLL)

# show where is header file
set_target_properties(TSL PROPERTIES PUBLIC_HEADER "${CMAKE_SOURCE_DIR}/tsl.hh")

target_include_directories(TSL PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/TSL>
)

install(TARGETS TSL CB EXPORT TSLTargets
  PUBLIC_HEADER DESTINATION include/TSL
)

install(EXPORT TSLTargets
  FILE TSLTargets.cmake
  NAMESPACE TSL::
  DESTINATION lib/cmake/TSL
)

install(FILES "TSLConfig.cmake"
  DESTINATION lib/cmake/TSL
)
