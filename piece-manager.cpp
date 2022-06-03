#include <cmath>

#include "piece-manager.hpp"

using chess::piece_manager_t;

piece_manager_t::piece_manager_t(): m_renderer { 64, "renderer-shader.vert", "piece-shader.frag" }, m_move_checker { *this }
{
    // Load the textures.
    m_renderer.set_texture("pawn.png", 0);
    m_renderer.set_texture("rook.png", 1);
    m_renderer.set_texture("knight.png", 2);
    m_renderer.set_texture("bishop.png", 3);
    m_renderer.set_texture("queen.png", 4);
    m_renderer.set_texture("king.png", 5);
    
    put_pieces_to_starting_place();
}

void piece_manager_t::set_dragging(bool p_dragging) noexcept
{
    // When draggin is turned off, a move has been made.
    if (!p_dragging && !m_dragged_piece.is_empty)
    {
        // Keep the old position for validation purposes
        auto previous_position = m_dragged_piece.position;
        
        auto new_piece_x {static_cast<uint8_t>(m_cursor_x)};
        auto new_piece_y {static_cast<uint8_t>(m_cursor_y)};
        
        m_dragged_piece.position = { new_piece_x, new_piece_y };
        
        if (m_move_checker.is_move_legal(m_dragged_piece, previous_position))
        {
            m_pieces[new_piece_x][new_piece_y] = m_dragged_piece;
            m_pieces[new_piece_x][new_piece_y].has_moved = true;
            m_flipped = !m_flipped;
        }
        else 
        {
            // Undo the move if it was found to be illegal
            m_dragged_piece.position = previous_position;
            m_pieces[previous_position.column][previous_position.row] = m_dragged_piece;
        }
        
        m_dragged_piece.is_empty = true;
        m_is_dragging = false;
    }
    else 
    {
        auto dragged_piece_x { static_cast<uint8_t>(m_cursor_x) };
        auto dragged_piece_y { static_cast<uint8_t>(m_cursor_y) };
        
        if ((m_pieces[dragged_piece_x][dragged_piece_y].is_empty) || (m_pieces[dragged_piece_x][dragged_piece_y].army == piece_t::army_e::BLACK && !m_flipped) || (m_pieces[dragged_piece_x][dragged_piece_y].army == piece_t::army_e::WHITE && m_flipped))
        {
            return;
        }
        
        m_dragged_piece = m_pieces[dragged_piece_x][dragged_piece_y];
        m_pieces[dragged_piece_x][dragged_piece_y].is_empty = true;
        m_is_dragging = true;
    }
}

namespace 
{
    double flip(double p_number, double p_pivot)
    {
        if (p_number > p_pivot)
        {
            return p_pivot - std::abs(p_number - p_pivot);
        }
        else if (p_number < p_pivot)
        {
            return p_pivot + std::abs(p_number - p_pivot);
        }
        else 
        {
            return 0.0;
        }
    }
}

void piece_manager_t::update_mouse_position(double p_x, double p_y)
{
    if (m_flipped)
    {
        m_cursor_y = flip(p_y, 4.0);
    }
    else 
    {
        m_cursor_y = p_y;
    }
    
    m_cursor_x = p_x;
}

void piece_manager_t::render_pieces()
{
    m_renderer.begin();
    
    for (auto i { static_cast<uint8_t>(0) }; i < 8; i++)
    {
        for (auto j { static_cast<uint8_t>(0) }; j < 8; j++)
        {
            if (m_flipped)
            {
                piece_t piece = get_piece({ i, j });
                piece.position.row = flip(piece.position.row, 3.5);
                piece.position.column = piece.position.column;
                
                draw_piece(piece);
            } else 
            {
                draw_piece(m_pieces[i][j]);
            }
        }
    }
    
    if (m_is_dragging)
    {
        draw_dragged_piece();
    }
    
    m_renderer.end();
}

void piece_manager_t::draw_piece(const piece_t& p_piece)
{
    if (p_piece.is_empty)
    {
        return;
    }
    
    renderer_t::quad_t piece {};
    piece.position = { static_cast<float>(p_piece.position.column), static_cast<float>(p_piece.position.row) };
    piece.size = { 1.0f, 1.0f };
    
    piece.uv.position = { 0.0f, 0.0f };
    piece.uv.size = { 1.0f, 1.0f };
    
    switch (p_piece.role)
    {
        case piece_t::role_e::PAWN:
            piece.texture = 0;
            break;
        case piece_t::role_e::ROOK:
            piece.texture = 1;
            break;
        case piece_t::role_e::KNIGHT:
            piece.texture = 2;
            break;
        case piece_t::role_e::BISHOP:
            piece.texture = 3;
            break;
        case piece_t::role_e::QUEEN:
            piece.texture = 4;
            break;
        case piece_t::role_e::KING:
            piece.texture = 5;
            break;
    }
    
    switch (p_piece.army)
    {
        case piece_t::army_e::WHITE:
            piece.color = { 1.0f, 1.0f, 1.0f, 1.0f };
            break;
        case piece_t::army_e::BLACK:
            piece.color = { 0.0f, 0.0f, 0.0f, 0.0f };
            break;
    }
    
    m_renderer.draw_quad(piece);
}

void piece_manager_t::draw_dragged_piece()
{
    if (m_dragged_piece.is_empty)
    {
        return;
    }
    
    renderer_t::quad_t piece {};
    
    if (m_flipped)
    {
        piece.position.x = static_cast<float>(m_cursor_x - 0.5);
        piece.position.y = static_cast<float>(flip(m_cursor_y + 0.5, 4));
    }
    else 
    {
        piece.position.x = static_cast<float>(m_cursor_x - 0.5);
        piece.position.y = static_cast<float>(m_cursor_y - 0.5);
    }
    
    piece.size = { 1.0f, 1.0f };
    
    piece.uv.position = { 0.0f, 0.0f };
    piece.uv.size = { 1.0f, 1.0f };
    
    switch (m_dragged_piece.role)
    {
        case piece_t::role_e::PAWN:
            piece.texture = 0;
            break;
        case piece_t::role_e::ROOK:
            piece.texture = 1;
            break;
        case piece_t::role_e::KNIGHT:
            piece.texture = 2;
            break;
        case piece_t::role_e::BISHOP:
            piece.texture = 3;
            break;
        case piece_t::role_e::QUEEN:
            piece.texture = 4;
            break;
        case piece_t::role_e::KING:
            piece.texture = 5;
            break;
    }
    
    switch (m_dragged_piece.army)
    {
        case piece_t::army_e::WHITE:
            piece.color = { 1.0f, 1.0f, 1.0f, 1.0f };
            break;
        case piece_t::army_e::BLACK:
            piece.color = { 0.0f, 0.0f, 0.0f, 0.0f };
            break;
    }
    
    m_renderer.draw_quad(piece);
}

void piece_manager_t::put_pieces_to_starting_place()
{
    // Add white pawns.
    for (auto i { static_cast<uint8_t>(0) }; i < 8; i++)
    {
        piece_t pawn {};
        pawn.is_empty = false;
        pawn.army = piece_t::army_e::WHITE;
        pawn.role = piece_t::role_e::PAWN;
        pawn.position = { i, 6 };
        
        m_pieces[i][6] = pawn;
    }
    
    // Add the black pawns.
    for (auto i { static_cast<uint8_t>(0) }; i < 8; i++)
    {
        piece_t pawn {};
        pawn.is_empty = false;
        pawn.army = piece_t::army_e::BLACK;
        pawn.role = piece_t::role_e::PAWN;
        pawn.position = { i, 1 };
        
        m_pieces[i][1] = pawn;
    }
    
    // Add the rooks
    {
        piece_t white_rook_1 {};
        white_rook_1.is_empty = false;
        white_rook_1.army = piece_t::army_e::WHITE;
        white_rook_1.role = piece_t::role_e::ROOK;
        white_rook_1.position = { 0, 7 };
        
        m_pieces[0][7] = white_rook_1;
        
        piece_t white_rook_2 {};
        white_rook_2.is_empty = false;
        white_rook_2.army = piece_t::army_e::WHITE;
        white_rook_2.role = piece_t::role_e::ROOK;
        white_rook_2.position = { 7, 7 };
        
        m_pieces[7][7] = white_rook_2;
        
        piece_t black_rook_1 {};
        black_rook_1.is_empty = false;
        black_rook_1.army = piece_t::army_e::BLACK;
        black_rook_1.role = piece_t::role_e::ROOK;
        black_rook_1.position = { 0, 0 };
        
        m_pieces[0][0] = black_rook_1;
        
        piece_t black_rook_2 {};
        black_rook_2.is_empty = false;
        black_rook_2.army = piece_t::army_e::BLACK;
        black_rook_2.role = piece_t::role_e::ROOK;
        black_rook_2.position = { 7, 0 };
        
        m_pieces[7][0] = black_rook_2;
    }
    
    // Add the knights
    {
        piece_t white_knight_1 {};
        white_knight_1.is_empty = false;
        white_knight_1.army = piece_t::army_e::WHITE;
        white_knight_1.role = piece_t::role_e::KNIGHT;
        white_knight_1.position = { 1, 7 };
        
        m_pieces[1][7] = white_knight_1;
        
        piece_t white_knight_2 {};
        white_knight_2.is_empty = false;
        white_knight_2.army = piece_t::army_e::WHITE;
        white_knight_2.role = piece_t::role_e::KNIGHT;
        white_knight_2.position = { 6, 7 };
        
        m_pieces[6][7] = white_knight_2;
        
        piece_t black_knight_1 {};
        black_knight_1.is_empty = false;
        black_knight_1.army = piece_t::army_e::BLACK;
        black_knight_1.role = piece_t::role_e::KNIGHT;
        black_knight_1.position = { 1, 0 };
        
        m_pieces[1][0] = black_knight_1;
        
        piece_t black_knight_2 {};
        black_knight_2.is_empty = false;
        black_knight_2.army = piece_t::army_e::BLACK;
        black_knight_2.role = piece_t::role_e::KNIGHT;
        black_knight_2.position = { 6, 0 };
        
        m_pieces[6][0] = black_knight_2;
    }
    
    // Add the bishops
    {
        piece_t white_bishop_1 {};
        white_bishop_1.is_empty = false;
        white_bishop_1.army = piece_t::army_e::WHITE;
        white_bishop_1.role = piece_t::role_e::BISHOP;
        white_bishop_1.position = { 2, 7 };
        
        m_pieces[2][7] = white_bishop_1;
        
        piece_t white_bishop_2 {};
        white_bishop_2.is_empty = false;
        white_bishop_2.army = piece_t::army_e::WHITE;
        white_bishop_2.role = piece_t::role_e::BISHOP;
        white_bishop_2.position = { 5, 7 };
        
        m_pieces[5][7] = white_bishop_2;
        
        piece_t black_bishop_1 {};
        black_bishop_1.is_empty = false;
        black_bishop_1.army = piece_t::army_e::BLACK;
        black_bishop_1.role = piece_t::role_e::BISHOP;
        black_bishop_1.position = { 2, 0 };
        
        m_pieces[2][0] = black_bishop_1;
        
        piece_t black_bishop_2 {};
        black_bishop_2.is_empty = false;
        black_bishop_2.army = piece_t::army_e::BLACK;
        black_bishop_2.role = piece_t::role_e::BISHOP;
        black_bishop_2.position = { 5, 0 };
        
        m_pieces[5][0] = black_bishop_2;
    }
    
    // Add the kings and queens
    {
        piece_t white_royal_1 {};
        white_royal_1.is_empty = false;
        white_royal_1.army = piece_t::army_e::WHITE;
        white_royal_1.role = piece_t::role_e::KING;
        white_royal_1.position = { 4, 7 };
        
        m_pieces[4][7] = white_royal_1;
        
        piece_t white_royal_2 {};
        white_royal_2.is_empty = false;
        white_royal_2.army = piece_t::army_e::WHITE;
        white_royal_2.role = piece_t::role_e::QUEEN;
        white_royal_2.position = { 3, 7 };
        
        m_pieces[3][7] = white_royal_2;
        
        piece_t black_royal_1 {};
        black_royal_1.is_empty = false;
        black_royal_1.army = piece_t::army_e::BLACK;
        black_royal_1.role = piece_t::role_e::KING;
        black_royal_1.position = { 4, 0 };
        
        m_pieces[4][0] = black_royal_1;
        
        piece_t black_royal_2 {};
        black_royal_2.is_empty = false;
        black_royal_2.army = piece_t::army_e::BLACK;
        black_royal_2.role = piece_t::role_e::QUEEN;
        black_royal_2.position = { 3, 0 };
        
        m_pieces[3][0] = black_royal_2;
    }
}