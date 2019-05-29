add_subdirectory(ai)
add_subdirectory(board)
add_subdirectory(listener)
add_subdirectory(pgn_parser)
add_subdirectory(move)
add_subdirectory(utils)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_HOME_DIRECTORY}/build
    )

add_executable(chessengine main.cc)

target_link_libraries(chessengine PRIVATE   ai
                                            board
                                            listener
                                            pgn_parser
                                            move
                                            utils
                                            Boost::program_options
                                            ${CMAKE_DL_LIBS}
                                            )
