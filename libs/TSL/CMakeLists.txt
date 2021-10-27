cmake_minimum_required(VERSION 3.14)
project(TakoStrLib)

# include dir with Ded's warnings
include(../../cmake/comp_flags.cmake)

# find logging library
find_package(TLL REQUIRED)

# indicate the documentation build
option(BUILD_DOC "Build documentation" OFF)
add_subdirectory(docs)

add_subdirectory(lib)
message(STATUS "Collected libs: ${LIBLIST}")

# common links and includes
foreach(LIB ${LIBLIST})
  # link with external library
  target_link_libraries(${LIB} TLL::TLL)

  # add sanitizers
  target_link_options(${LIB} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}>>")
  target_compile_options(${LIB} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}>>")

  # add warnings
  target_compile_options(${LIB} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_GCC_WARNS_LST}>>")

  # specify standard
  target_compile_features(${LIB} PRIVATE cxx_std_11)

  # include directories for build and install modes
  target_include_directories(${LIB} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIB}>
    $<INSTALL_INTERFACE:include>
  )
endforeach()

# special links and includes
target_link_libraries(FileSys CharBuf)
target_include_directories(FileSys PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/CharBuf)

target_link_libraries(TSL CharBuf)
target_include_directories(TSL PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/CharBuf)

# installation rules
install(TARGETS ${LIBLIST} EXPORT TSLTargets)

install(EXPORT TSLTargets
  FILE TSLTargets.cmake
  NAMESPACE TSL::
  DESTINATION lib/cmake/TSL
)

install(FILES "TSLConfig.cmake"
  DESTINATION lib/cmake/TSL
)
