add_library(FileSys STATIC filesys.cc)

# show where is header file
set_target_properties(FileSys PROPERTIES PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/FileSys/filesys.hh")
