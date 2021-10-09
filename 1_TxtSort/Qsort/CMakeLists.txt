project(TxtSort)

# TQS - Tako's Quick Sort
add_library(TQS tqsort.cc)
target_include_directories(TQS INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
