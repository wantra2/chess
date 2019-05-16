add_subdirectory(ai)
add_subdirectory(board)
add_subdirectory(listener)
add_subdirectory(pgn_parser)

add_executable(chessengine main.cc)

target_link_libraries(chessengine PRIVATE   ai
                                            board
                                            listener
                                            pgn_parser)
