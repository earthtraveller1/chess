#ifndef E7CEE28C_3498_4BFD_ACF5_31F521F7EB2B
#define E7CEE28C_3498_4BFD_ACF5_31F521F7EB2B

#include <cstdint>

namespace chess
{
// The position of a piece
struct piece_position_t
{
    uint8_t column{0};
    uint8_t row{0};

    inline bool operator!=(const piece_position_t &b)
    {
        return ((column != b.column) || (row != b.row));
    }
};
} // namespace chess

#endif /* E7CEE28C_3498_4BFD_ACF5_31F521F7EB2B */
