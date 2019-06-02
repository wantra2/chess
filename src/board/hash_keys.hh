#pragma once

#include <cstdlib>
#include "board/position.hh"

#define RAND_64 	((uint64_t)rand() | \
					(uint64_t)rand() << 15 | \
					(uint64_t)rand() << 30 | \
					(uint64_t)rand() << 45 | \
					((uint64_t)rand() & 0xf) << 60 )

namespace board
{
    struct hash_keys
    {
        uint64_t piece_keys[13][SQUARE_NB];
        uint64_t side_key;
    };

    extern hash_keys h_keys;
    void init_hash_keys(hash_keys& hashkeys);
}