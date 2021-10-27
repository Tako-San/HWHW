cmake_minimum_required(VERSION 3.15)
project(ASMR)

include(../cmake/clang_format.cmake)

find_package(TLL REQUIRED)
find_package(TSL REQUIRED)

set(EXTERN_LIBS TSL::TSL TSL::CharBuf TSL::FileSys TLL::TLL)

add_subdirectory(lib)
message(STATUS "Collected libs: ${LIBLIST}")
foreach(LIB ${LIBLIST})
  target_include_directories(${LIB} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_compile_features(${LIB} PRIVATE cxx_std_20)
  target_link_libraries(${LIB} PRIVATE ${EXTERN_LIBS})

  # add sanitizers
  target_link_options(${LIB} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}>>")
  target_compile_options(${LIB} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}>>")

  # add warnings
  target_compile_options(${LIB} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_GCC_WARNS_LST}>>")
endforeach()

add_subdirectory(tools)
message(STATUS "Collected tools: ${TOOLLIST}")

foreach(TOOL ${TOOLLIST})
  target_include_directories(${TOOL} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_compile_features(${TOOL} PRIVATE cxx_std_20)
  target_link_libraries(${TOOL} PRIVATE ${EXTERN_LIBS})

  # add sanitizers
  target_link_options(${TOOL} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}>>")
  target_compile_options(${TOOL} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_SAN_LST}>>")

  # add warnings
  target_compile_options(${TOOL} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:Debug>:${DED_GCC_WARNS_LST}>>")

endforeach()
