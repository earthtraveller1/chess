#include "piece-manager.hpp"
#include "piece.hpp"
#include "piece-position.hpp"
#include <iostream>
// #include <unistd.h>
#include <signal.h>
#include "utilities.hpp"

#include "move-checker.hpp"

using chess::move_checker_t;

namespace
{
    bool operator==(const chess::piece_position_t& a, const chess::piece_position_t& b)
    {
        return ((a.column == b.column) && (a.row == b.row));
    }
}

move_checker_t::move_checker_t(chess::piece_manager_t& p_piece_manager): m_piece_manager { p_piece_manager }
{
    
}

bool move_checker_t::is_move_legal(const piece_t& p_piece, const piece_position_t& p_original_position, bool p_check_for_check)
{
    // This prevents you from skipping a move by dragging and dropping a piece
    // back into it's original position
    if (p_piece.position == p_original_position)
    {
        return false;
    }
    
    // Prevent capturing of allies
    if (!(m_piece_manager.m_pieces[p_piece.position.column][p_piece.position.row].is_empty) && m_piece_manager.m_pieces[p_piece.position.column][p_piece.position.row].army == p_piece.army)
    {
        return false;
    }
    
    // Only knights can jump over pieces
    if (!is_space_in_between_empty(p_piece.position, p_original_position) && (p_piece.role != piece_t::role_e::KNIGHT))
    {
        return false;
    }
    
    // Check if the move results in the king becoming checked
    if (p_check_for_check)
    {
        // Create a copy of the piece positions
        auto old_piece_positions { m_piece_manager.m_pieces };
        
        // Perform the move.
        m_piece_manager.get_piece(p_piece.position) = p_piece;
        m_piece_manager.get_piece(p_piece.position).is_empty = false;
        m_piece_manager.get_piece(p_original_position).is_empty = true;
        
        auto result { true };
        
        // Get the king
        piece_position_t king {};
        
        for (auto& column: m_piece_manager.m_pieces)
        {
            for (auto& piece: column)
            {
                if ((piece.army == p_piece.army) && (piece.role == piece_t::role_e::KING) && (!piece.is_empty))
                {
                    king = piece.position;
                }
            }
        }
        
        // Check if any of enemy pieces can capture the king
        if (is_space_attacked(king, (p_piece.army == piece_t::army_e::WHITE ? piece_t::army_e::BLACK : piece_t::army_e::WHITE)))
        {
            result = false;
        }
        
        m_piece_manager.m_pieces = old_piece_positions;
        
        if (!result)
        {
            return false;
        }
    }
    
    // Different pieces have different moving rules.
    switch (p_piece.role)
    {
        case piece_t::role_e::ROOK:
            return 
            (
                (
                    p_piece.position.column == p_original_position.column
                ) 
                || 
                (
                    p_piece.position.row == p_original_position.row
                )
            );
        case piece_t::role_e::BISHOP:
            return 
            (
                std::abs
                (
                    p_piece.position.column - p_original_position.column
                ) 
                == 
                std::abs
                (
                    p_piece.position.row - p_original_position.row
                )
            );
        case piece_t::role_e::KNIGHT:
            return 
            (
                (
                    (
                        std::abs
                        (
                            p_piece.position.column - p_original_position.column
                        ) == 1
                    ) 
                    && 
                    (
                        std::abs
                        (
                            p_piece.position.row - p_original_position.row
                        ) == 2
                    )
                ) 
                || 
                (
                    (
                        std::abs
                        (
                            p_piece.position.column - p_original_position.column
                        ) == 2
                    ) 
                    && 
                    (
                        std::abs
                        (
                            p_piece.position.row - p_original_position.row
                        ) == 1
                    )
                )
            );
        case piece_t::role_e::KING:
            return 
            (
                (
                    std::abs
                    (
                        p_piece.position.column - p_original_position.column
                    ) <= 1
                ) 
                && 
                (
                    std::abs
                    (
                        p_piece.position.row - p_original_position.row
                    ) <= 1
                )
            );
        case piece_t::role_e::QUEEN:
            return 
            (
                (
                    (
                        p_piece.position.column == p_original_position.column
                    ) 
                    || 
                    (
                        p_piece.position.row == p_original_position.row
                    )
                ) 
                || 
                (
                    std::abs
                    (
                        p_piece.position.column - p_original_position.column
                    ) 
                    == 
                    std::abs
                    (
                        p_piece.position.row - p_original_position.row
                    )
                )
            );
        case piece_t::role_e::PAWN:
            return is_pawn_move_legal(p_piece, p_original_position);
        default:
            return true;
    }
}

bool move_checker_t::should_promote(const piece_t& p_piece) const
{
    if (p_piece.role == piece_t::role_e::PAWN)
    {
        if (p_piece.army == piece_t::army_e::WHITE)
        {
            return (p_piece.position.row == 0);
        }
        else 
        {
            return (p_piece.position.row == 7);
        }
    }
    else 
    {
        return false;
    }
}

void move_checker_t::handle_castling(const piece_t& p_piece)
{
    // The piece being moved has to be a King that has not moved yet.
    if (p_piece.role == piece_t::role_e::KING && !p_piece.has_moved)
    {
        // Determine the row of the rook.
        auto rook_row { p_piece.army == piece_t::army_e::WHITE ? static_cast<uint8_t>(7) : static_cast<uint8_t>(0) };
        
        // King-side castling
        if (p_piece.position.column == 6)
        {
            // The target rook cannot haved moved yet.
            if (m_piece_manager.get_piece({ 7, rook_row }).has_moved)
                return;
            
            
        }
        
        // Queen-side castling
        else if (p_piece.position.column == 2)
        {
            // The target rook cannot haved moved yet.
            if (m_piece_manager.get_piece({ 0, rook_row }).has_moved)
                return;
            
            
        }
    }
    else 
    {
        return;
    }
}

bool move_checker_t::is_pawn_move_legal(const piece_t& p_piece, const piece_position_t& p_original_position)
{
    if (p_piece.army == piece_t::army_e::WHITE)
    {
        if ((p_piece.position.row == (p_original_position.row - 1)) || (!p_piece.has_moved && (p_piece.position.row == (p_original_position.row - 2))))
        {
            if ((p_piece.position.column == p_original_position.column) && m_piece_manager.get_piece(p_piece.position).is_empty)
            {
                return true;
            }
            
            if (std::abs(p_piece.position.column - p_original_position.column) == 1 && !(m_piece_manager.get_piece(p_piece.position).is_empty))
            {
                return true;
            }
            
            return false;
        }
        else 
        {
            return false;
        }
    }
    else if (p_piece.army == piece_t::army_e::BLACK)
    {
        if ((p_piece.position.row == (p_original_position.row + 1)) || (!p_piece.has_moved && (p_piece.position.row == (p_original_position.row + 2))))
        {
            if ((p_piece.position.column == p_original_position.column) && m_piece_manager.get_piece(p_piece.position).is_empty)
            {
                return true;
            }
            
            if (std::abs(p_piece.position.column - p_original_position.column) == 1 && !(m_piece_manager.get_piece(p_piece.position).is_empty))
            {
                return true;
            }
            
            return false;
        }
        else 
        {
            return false;
        }
    }
    else 
    {
        return false;
    }
}

#define neng if (i == 6 && j == 5) raise(SIGTRAP)

bool move_checker_t::is_space_in_between_empty(const piece_position_t& p_a, const piece_position_t& p_b)
{
    // If the two spaces are adjacent, then return true.
    if (std::abs(p_a.row - p_b.row) <= 1 && std::abs(p_a.column - p_b.column) <= 1)
    {
        return true;
    }
    
    auto column_increment { static_cast<int8_t>(0) };
    auto row_increment { static_cast<int8_t>(0) };
    
    if (p_b.column == p_a.column)
    {
        column_increment = 0;
    }
    else if (p_b.column > p_a.column)
    {
        column_increment = 1;
    }
    else if (p_b.column < p_a.column)
    {
        column_increment = -1;
    }
        
    if (p_b.row == p_a.row)
    {
        row_increment = 0;
    }
    else if (p_b.row > p_a.row)
    {
        row_increment = 1;
    }
    else if (p_b.row < p_a.row)
    {
        row_increment = -1;
    }
    
    for (auto i { p_a.column + column_increment }, j { p_a.row + row_increment }; (i != p_b.column) && (j != p_b.row); i += column_increment, j += row_increment)
    {
        if (!(m_piece_manager.m_pieces[i][j].is_empty))
        {
            return false;
        }
    }
    
    return true;
}

bool move_checker_t::is_space_attacked(const piece_position_t& p_position, piece_t::army_e p_enemy_army)
{
    for (const auto& column: m_piece_manager.m_pieces)
    {
        for (const auto& i_piece: column)
        {
            if (i_piece.army == p_enemy_army)
            {
                auto piece { i_piece };
                auto original_position { i_piece.position };
                piece.position = p_position;
                
                if (is_move_legal(piece, original_position, false))
                {
                    return true;
                }
            }
        }
    }
    
    return false;
}