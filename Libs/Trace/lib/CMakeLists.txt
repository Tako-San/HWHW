# TLL - Tako's logging library
add_library(TLL trace.cc)

# show where is header file
set_target_properties(TLL PROPERTIES PUBLIC_HEADER "${CMAKE_SOURCE_DIR}/include/trace.hh")


target_include_directories(TLL PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> 
    $<INSTALL_INTERFACE:include/TLL>  # <prefix>/include/mylib
)

install(TARGETS TLL EXPORT TLLTargets
  PUBLIC_HEADER DESTINATION include/TLL
)

install(EXPORT TLLTargets
  FILE TLLTargets.cmake
  NAMESPACE TLL::
  DESTINATION lib/cmake/TLL
)

install(FILES "TLLConfig.cmake"
  DESTINATION lib/cmake/TLL
)
