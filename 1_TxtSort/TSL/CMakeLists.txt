project(TxtSort)

# TSL - Tako's string library
add_library(TSL tsl.cc)
target_include_directories(TSL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TSL CB TLL)
