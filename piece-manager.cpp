#include "piece-manager.hpp"

using chess::piece_manager_t;

piece_manager_t::piece_manager_t(): m_renderer { 64, "renderer-shader.vert", "piece-shader.frag" }
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

void piece_manager_t::render_pieces()
{
    m_renderer.begin();
    
    for (auto i { static_cast<uint8_t>(0) }; i < 8; i++)
    {
        for (auto j { static_cast<uint8_t>(0) }; j < 8; j++)
        {
            draw_piece(m_pieces[i][j]);
        }
    }
    
    m_renderer.end();
}

void piece_manager_t::draw_piece(piece_t p_piece)
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
}