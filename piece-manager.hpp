#ifndef D3B264AE_83D2_4309_85D9_5D151A9D9EB3
#define D3B264AE_83D2_4309_85D9_5D151A9D9EB3

#include <array>

#include "renderer.hpp"

namespace chess
{
    class piece_manager_t
    {
    public:
        // Constructor
        piece_manager_t();
        
        // Render the pieces
        void render_pieces();
        
    private:
        // The renderer used to render the stuff.
        renderer_t m_renderer;
        
        // The pieces that can be renderered by the renderer.
        renderer_t::quad_t m_pawn;
        renderer_t::quad_t m_rook;
        renderer_t::quad_t m_knight;
        renderer_t::quad_t m_bishop;
        renderer_t::quad_t m_queen;
        renderer_t::quad_t m_king;
        
        // The position of a piece
        struct piece_position_t
        {
            uint8_t column { 0 };
            uint8_t row { 0 };
        };
        
        // A piece
        struct piece_t
        {
            piece_t() {}
            
            // Is the piece empty?
            bool is_empty { true };
            
            piece_position_t position;
            
            enum class army_e
            {
                WHITE, BLACK
            } army { army_e::WHITE };
            
            enum class role_e
            {
                PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
            } role { role_e::PAWN };
        };
        
        // A 2D array representing the entire array of pieces on the board.
        std::array<std::array<piece_t, 8>, 8> m_pieces;
        
        // Utility functions for drawing specific pieces.
        void draw_pawn(uint8_t x_position, uint8_t y_position, piece_t::army_e army);
        
        // Put pieces back into their starting place.
        void put_pieces_to_starting_place();
        
        // Set the quad configuration structs for the pieces
        void initialize_piece_quads();
    };
}

#endif /* D3B264AE_83D2_4309_85D9_5D151A9D9EB3 */
