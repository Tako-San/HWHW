project(TxtSort)

add_library(CB CharBuf.cc)
target_include_directories(CB INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
