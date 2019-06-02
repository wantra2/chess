#include "board/hash_keys.hh"

namespace board
{
    hash_keys h_keys = {};

    void init_hash_keys(hash_keys& hashkeys)
    {
        hashkeys.side_key = 0x1234567891234567;
        for (int i = 0; i < 13; ++i)
        {
            for (int j = A1; j < SQUARE_NB; ++j)
                hashkeys.piece_keys[i][j] = RAND_64;
        }
    }
}