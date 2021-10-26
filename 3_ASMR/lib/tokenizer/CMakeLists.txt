set(SRCS tokenizer.cc)
add_library(tokenizer ${SRCS})

format_target(tokenizer ${CMAKE_CURRENT_SOURCE_DIR} ${SRCS})
