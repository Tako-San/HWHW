set(SRCS asm.cc)
add_library(asm ${SRCS})

format_target(asm ${CMAKE_CURRENT_SOURCE_DIR} ${SRCS})
