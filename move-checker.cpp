#include "piece-manager.hpp"
#include "piece.hpp"
#include "piece-position.hpp"

#include "move-checker.hpp"

using chess::move_checker_t;

move_checker_t::move_checker_t(chess::piece_manager_t& p_piece_manager): m_piece_manager { p_piece_manager }
{
    
}

bool move_checker_t::is_move_legal(const piece_t& p_piece, const piece_position_t& p_original_position, bool p_check_for_check)
{
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

bool move_checker_t::is_space_in_between_empty(const piece_position_t& p_a, const piece_position_t& p_b)
{
    if (p_a.row == p_b.row)
    {
        uint8_t a;
        uint8_t b;
        
        if (p_a.column > p_b.column)
        {
            a = p_b.column;
            b = p_a.column;
        }
        else 
        {
            a = p_a.column;
            b = p_b.column;
        }
        
        for (auto i { a + 1 }; i < b; i++)
        {
            if (!m_piece_manager.m_pieces[i][p_a.row].is_empty)
            {
                return false;
            }
        }
        
        return true;
    }
    else if (p_a.column == p_b.column)
    {
        uint8_t a;
        uint8_t b;
        
        if (p_a.row > p_b.row)
        {
            a = p_b.row;
            b = p_a.row;
        }
        else 
        {
            a = p_a.row;
            b = p_b.row;
        }
        
        for (auto i { a + 1 }; i < b; i++)
        {
            if (!m_piece_manager.m_pieces[p_a.column][i].is_empty)
            {
                return false;
            }
        }
        
        return true;
    }
    else 
    {
        piece_position_t a {};
        piece_position_t b {};
        
        if ((p_a.row > p_b.row) && (p_a.column < p_b.column))
        {
            a = p_a;
            b = p_b;
            
            for (auto i { a.column + 1 }, j { a.row - 1}; i > b.column, j < b.row; i--, j++)
            {
                if (!(m_piece_manager.m_pieces[i][j].is_empty))
                {
                    return false;
                }
            }
        }
        else if ((p_a.column > p_b.column) && (p_a.row < p_b.row))
        {
            a = p_a;
            b = p_b;
            
            for (auto i { a.column - 1 }, j { a.row + 1}; i < b.column, j < b.row; i--, j++)
            {
                if (!(m_piece_manager.m_pieces[i][j].is_empty))
                {
                    return false;
                }
            }
        }
        else 
        {
            if (p_a.row > p_b.row)
            {
                a = p_b;
                b = p_a;
            }
            else 
            {
                a = p_a;
                b = p_b;
            }
            
            for (auto i { a.column + 1 }, j { a.row + 1}; i < b.column, j < b.row; i++, j++)
            {
                if (!(m_piece_manager.m_pieces[i][j].is_empty))
                {
                    return false;
                }
            }
        }
        
        return true;
    }
}