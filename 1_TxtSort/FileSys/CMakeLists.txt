project(TxtSort)

# TFL - Tako's filesystem library
add_library(TFL filesys.cc)

target_include_directories(TFL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../TLL)
target_include_directories(TFL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../TSL)
target_include_directories(TFL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TFL TLL TSL)
