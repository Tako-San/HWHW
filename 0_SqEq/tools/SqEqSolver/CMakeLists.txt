set(SRCS main.cc tests.cc)

add_executable(SqEqSolver ${SRCS})
target_include_directories(SqEqSolver PRIVATE ${CMAKE_BINARY_DIR})
