#ifndef D693ECB4_1C50_4E02_9987_E164647B99BF
#define D693ECB4_1C50_4E02_9987_E164647B99BF

#include "piece-manager.hpp"

namespace chess
{
    class move_checker_t
    {
    public:
        // Constructor requires a piece manager since checking moves requires 
        // referencing the rest of the board and other pieces.
        move_checker_t(piece_manager_t& piece_manager);
        
        // Returns if the move is legal or not.
        bool is_move_legal(const piece_manager_t::piece_t& piece, const piece_manager_t::piece_position_t& previous_position);
        
    private:
        // The piece manager for reference purposes
        piece_manager_t& m_piece_manager;
        
        // Pawn move checker has been moved to a different function by itself 
        // due to it's complexity
        bool is_pawn_move_legal(const piece_manager_t::piece_t& piece, const piece_manager_t::piece_position_t& previous_position);
        
        // Check if there's any non-empty pieces between two positons.
        bool is_space_in_between_empty(const piece_manager_t::piece_position_t& a, const piece_manager_t::piece_position_t& b);
    };
}

#endif /* D693ECB4_1C50_4E02_9987_E164647B99BF */
