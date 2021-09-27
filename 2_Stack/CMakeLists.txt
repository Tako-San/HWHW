cmake_minimum_required(VERSION 3.10)

# set project name
project(Stack VERSION 0.1)

# add sanitizers
if (CMAKE_BUILD_TYPE MATCHES "^[Dd]ebug")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
endif()

add_executable(${PROJECT_NAME} main.cc)
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/Stack")

# target_link_libraries(${PROJECT_NAME} STK)

# specify standard
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

# add warnings
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra)
