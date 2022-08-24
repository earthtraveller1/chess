#ifndef E60BF8AD_E940_460A_A0A2_7B4BC2F7843C
#define E60BF8AD_E940_460A_A0A2_7B4BC2F7843C

#include "piece-position.hpp"

namespace chess
{
// A piece
struct piece_t
{
    piece_t() {}

    // Is the piece empty?
    bool is_empty{true};

    // Has the peice moved at all yet?
    bool has_moved{false};

    // Can the piece be captured through en passant?
    bool can_be_en_passant_captured{false};

    piece_position_t position;

    enum class army_e
    {
        WHITE = 0,
        BLACK
    } army{army_e::WHITE};

    enum class role_e
    {
        PAWN = 0,
        ROOK,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING
    } role{role_e::PAWN};
};
} // namespace chess

#endif /* E60BF8AD_E940_460A_A0A2_7B4BC2F7843C */
