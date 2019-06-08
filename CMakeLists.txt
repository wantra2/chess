cmake_minimum_required(VERSION 3.0.0)
project(chess VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


find_package(Boost COMPONENTS program_options REQUIRED)

#add_compile_options(-march=native -flto -static -Wall -Wextra -std=c++17 -O3)
add_compile_options(-g -Wall -Wextra -std=c++17 -O0)

include_directories("${PROJECT_SOURCE_DIR}/src")

add_subdirectory(tests)
add_subdirectory(src)

add_executable(chessengine src/main.cc)

target_link_libraries(chessengine PRIVATE   ai
        board
        listener
        pgn_parser
        move
        utils
        Boost::program_options
        ${CMAKE_DL_LIBS}
        )
