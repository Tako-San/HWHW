set(SRCS main.cc)
add_executable(disassembler ${SRCS})
format_target(disassembler ${CMAKE_CURRENT_SOURCE_DIR} ${SRCS})