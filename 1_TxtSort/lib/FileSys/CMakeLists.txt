add_library(FileSys filesys.cc)

find_package(TLL REQUIRED)
target_link_libraries(FileSys TLL::TLL)

find_package(TSL REQUIRED)
target_link_libraries(FileSys TSL::TSL)
