#include "piece-manager.hpp"

using chess::piece_manager_t;

piece_manager_t::piece_manager_t(): m_renderer { 64, "renderer-shader.vert", "piece-shader.frag" }
{
    // Load the textures.
    m_renderer.set_texture("pawn.png", 0);
    
    // Initialize the structurs containing information related to the pieces.
    m_pawn.size.x = 1.0f;
    m_pawn.size.y = 1.0f;
    m_pawn.position.x = 0.0f;
    m_pawn.position.y = 0.0f;
    m_pawn.uv.position = { 0.0f, 0.0f };
    m_pawn.uv.size = { 1.0f, 1.0f };
    m_pawn.color = { 0.0f, 0.0f, 0.0f, 0.0f };
    m_pawn.texture = 0;
    
    // Add white pawns.
    for (auto i { static_cast<uint8_t>(0) }; i < 8; i++)
    {
        piece_t pawn {};
        pawn.is_empty = false;
        pawn.army = piece_t::army_e::WHITE;
        pawn.role = piece_t::role_e::PAWN;
        pawn.position = { i, 6 };
        
        m_pieces[i][1] = pawn;
    }
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