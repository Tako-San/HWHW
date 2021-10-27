set(SRCS main.cc assembler.cc)
add_executable(assembler ${SRCS})

format_target(assembler ${CMAKE_CURRENT_SOURCE_DIR} ${SRCS})
