set(SRCS main.cc)
add_executable(processor ${SRCS})
format_target(processor ${CMAKE_CURRENT_SOURCE_DIR} ${SRCS})
