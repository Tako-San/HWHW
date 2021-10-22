add_library(SqEq STATIC SqEq.cc)

# because we want use object file anywhere
target_compile_options(SqEq PRIVATE -fPIE)

# show where is header file
set_target_properties(SqEq PROPERTIES PUBLIC_HEADER "${CMAKE_SOURCE_DIR}/include/SqEq.hh")

target_include_directories(SqEq PUBLIC  
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include/SqEq>  # <prefix>/include/mylib
)

install(TARGETS SqEq EXPORT SqEqTargets
  PUBLIC_HEADER DESTINATION include/SqEq
)

install(EXPORT SqEqTargets
  FILE SqEqTargets.cmake
  NAMESPACE SqEq::
  DESTINATION lib/cmake/SqEq
)

install(FILES "SqEqConfig.cmake"
  DESTINATION lib/cmake/SqEq
)
