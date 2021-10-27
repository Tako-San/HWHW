add_library(TSL tsl.cc)

# show where is header file
set_target_properties(TSL PROPERTIES PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/TSL/tsl.hh")
