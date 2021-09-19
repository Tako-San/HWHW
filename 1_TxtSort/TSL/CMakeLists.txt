add_library(TSL tsl.cc)

target_include_directories(TSL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/CharBuf)
target_include_directories(TSL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TSL PUBLIC CB)
target_link_libraries(TSL PUBLIC TLL)
