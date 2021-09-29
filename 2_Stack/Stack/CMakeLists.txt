project(Stack)

add_library(StackImpl stack.cc)

target_include_directories(StackImpl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
