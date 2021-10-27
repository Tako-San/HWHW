add_library(CB STATIC CharBuf.cc)

# show where is header file
set_target_properties(CB PROPERTIES PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/CharBuf.hh")

target_include_directories(CB INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
