cmake_minimum_required(VERSION 3.0.0)
project(chess VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


find_package(Boost COMPONENTS program_options REQUIRED)

add_compile_options(-march=native -flto -static -Wall -Wextra -std=c++17 -O3)

include_directories("${PROJECT_SOURCE_DIR}/src")

add_subdirectory(tests)
add_subdirectory(src)
