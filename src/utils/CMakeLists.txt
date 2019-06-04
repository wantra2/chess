set(
        MISC_SRC misc.cc
                options.cc
                perft.cc
   )
add_library(utils ${MISC_SRC})

target_link_libraries(utils
                        Boost::program_options)
