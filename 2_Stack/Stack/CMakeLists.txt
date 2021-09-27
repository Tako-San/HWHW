project(Stack)

add_library(STK stack.hh)

target_include_directories(STK INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
