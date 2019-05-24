set(BOARD_SRC pgn-move.cc
              board.cc
              piece-type.cc
              board-adapter.cc
              bitboard.cc
              position.cc
                   )

add_library(board ${BOARD_SRC})
