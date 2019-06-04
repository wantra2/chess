set(PGN_PARSER_SRC pgn-exception.cc
                   pgn-parser.cc
                   pgn.cc
                   )

add_library(pgn_parser ${PGN_PARSER_SRC})

target_link_libraries(pgn_parser board)
