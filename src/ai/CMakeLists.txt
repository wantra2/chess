set(AI_SRC uci.cc
            eval.cc
            minmax.cc)

add_library(ai ${AI_SRC})

target_link_libraries(ai board)