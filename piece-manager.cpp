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
    
    initialize_piece_quads();
    put_pieces_to_starting_place();
}

void piece_manager_t::render_pieces()
{
    m_renderer.begin();
    
    for (auto i { static_cast<uint8_t>(0) }; i < 8; i++)
    {
        for (auto j { static_cast<uint8_t>(0) }; j < 8; j++)
        {
            piece_t& piece = m_pieces[i][j];
            
            if (!piece.is_empty)
            {
                switch (piece.role)
                {
                    case piece_t::role_e::PAWN:
                        draw_pawn(piece.position.column, piece.position.row, piece.army);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    
    m_renderer.end();
}

void piece_manager_t::draw_pawn(uint8_t x_position, uint8_t y_position, piece_t::army_e army)
{
    auto pawn { m_pawn };
    pawn.position = { static_cast<float>(x_position), static_cast<float>(y_position) };
    
    switch (army)
    {
        case piece_t::army_e::WHITE:
            pawn.color = { 1.0f, 1.0f, 1.0f, 1.0f };
            break;
        case piece_t::army_e::BLACK:
            pawn.color = { 0.0f, 0.0f, 0.0f, 0.0f };
            break;
    }
    
    m_renderer.draw_quad(pawn);
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
        white_rook_1.is_empty = false;
        white_rook_1.army = piece_t::army_e::WHITE;
        white_rook_1.role = piece_t::role_e::ROOK;
        white_rook_1.position = { 7, 7 };
        
        m_pieces[7][7] = white_rook_2;
        
        piece_t black_rook_1 {};
        white_rook_1.is_empty = false;
        white_rook_1.army = piece_t::army_e::BLACK;
        white_rook_1.role = piece_t::role_e::ROOK;
        white_rook_1.position = { 0, 0 };
        
        m_pieces[0][0] = black_rook_1;
        
        piece_t black_rook_2 {};
        white_rook_1.is_empty = false;
        white_rook_1.army = piece_t::army_e::BLACK;
        white_rook_1.role = piece_t::role_e::ROOK;
        white_rook_1.position = { 7, 0 };
        
        m_pieces[7][0] = black_rook_1;
    }
}

void piece_manager_t::initialize_piece_quads()
{
    m_pawn.size.x = 1.0f;
    m_pawn.size.y = 1.0f;
    m_pawn.position.x = 0.0f;
    m_pawn.position.y = 0.0f;
    m_pawn.uv.position = { 0.0f, 0.0f };
    m_pawn.uv.size = { 1.0f, 1.0f };
    m_pawn.color = { 0.0f, 0.0f, 0.0f, 0.0f };
    m_pawn.texture = 0;
    
    m_rook.size.x = 1.0f;
    m_rook.size.y = 1.0f;
    m_rook.position.x = 0.0f;
    m_rook.position.y = 0.0f;
    m_rook.uv.position = { 0.0f, 0.0f };
    m_rook.uv.size = { 1.0f, 1.0f };
    m_rook.color = { 0.0f, 0.0f, 0.0f, 0.0f };
    m_rook.texture = 1;
    
    m_knight.size.x = 1.0f;
    m_knight.size.y = 1.0f;
    m_knight.position.x = 0.0f;
    m_knight.position.y = 0.0f;
    m_knight.uv.position = { 0.0f, 0.0f };
    m_knight.uv.size = { 1.0f, 1.0f };
    m_knight.color = { 0.0f, 0.0f, 0.0f, 0.0f };
    m_knight.texture = 2;
    
    m_bishop.size.x = 1.0f;
    m_bishop.size.y = 1.0f;
    m_bishop.position.x = 0.0f;
    m_bishop.position.y = 0.0f;
    m_bishop.uv.position = { 0.0f, 0.0f };
    m_bishop.uv.size = { 1.0f, 1.0f };
    m_bishop.color = { 0.0f, 0.0f, 0.0f, 0.0f };
    m_bishop.texture = 3;
    
    m_queen.size.x = 1.0f;
    m_queen.size.y = 1.0f;
    m_queen.position.x = 0.0f;
    m_queen.position.y = 0.0f;
    m_queen.uv.position = { 0.0f, 0.0f };
    m_queen.uv.size = { 1.0f, 1.0f };
    m_queen.color = { 0.0f, 0.0f, 0.0f, 0.0f };
    m_queen.texture = 4;
    
    m_king.size.x = 1.0f;
    m_king.size.y = 1.0f;
    m_king.position.x = 0.0f;
    m_king.position.y = 0.0f;
    m_king.uv.position = { 0.0f, 0.0f };
    m_king.uv.size = { 1.0f, 1.0f };
    m_king.color = { 0.0f, 0.0f, 0.0f, 0.0f };
    m_king.texture = 5;
}