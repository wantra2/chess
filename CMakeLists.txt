cmake_minimum_required(VERSION 3.0.0)
project(chess VERSION 0.1.0)

include(CTest)
enable_testing()

find_package( Boost REQUIRED COMPONENTS program_options )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_compile_options(-Wall -Wextra -std=c++17 -fno-tree-vectorize -g -O0)

include_directories("${PROJECT_SOURCE_DIR}/src")

add_subdirectory(tests)
add_subdirectory(src)
