project(TxtSort)

# TLL - Tako's logging library
add_library(TLL trace.cc)
target_include_directories(TLL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TLL CB)
