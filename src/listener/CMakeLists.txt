set(LISTENER_SRC basic_logger.cc
                   )

add_library(listener ${LISTENER_SRC})

target_link_libraries(listener board)