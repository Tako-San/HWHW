set(SRCS main.cc)
add_executable(assembler ${SRCS})
format_target(assembler ${CMAKE_CURRENT_SOURCE_DIR} ${SRCS})
