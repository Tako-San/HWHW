add_library(STK stack.cc)

# show where is header file
set_target_properties(STK PROPERTIES PUBLIC_HEADER "${CMAKE_SOURCE_DIR}/include/stack.hh")


target_include_directories(STK PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS STK EXPORT STKTargets)

install(EXPORT STKTargets
  FILE STKTargets.cmake
  NAMESPACE STK::
  DESTINATION lib/cmake/STK
)

install(FILES "STKConfig.cmake"
  DESTINATION lib/cmake/STK
)