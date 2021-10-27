add_library(CharBuf STATIC CharBuf.cc)

# show where is header file
set_target_properties(CharBuf PROPERTIES PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/CharBuf/CharBuf.hh")
